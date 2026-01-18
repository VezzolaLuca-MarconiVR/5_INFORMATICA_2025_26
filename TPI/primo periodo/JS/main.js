// main.js - Histogram streaming version

const fileInput = document.getElementById("fileInput");
const startBtn = document.getElementById("startBtn");
const cancelBtn = document.getElementById("cancelBtn");
const statusEl = document.getElementById("status");
const progressFill = document.getElementById("progressFill");
const maxPointsInput = document.getElementById("maxPoints"); // not used for histogram
const batchSizeInput = document.getElementById("batchSize");
const binsInput =
  document.getElementById("binsInput") ||
  (() => {
    // create a fallback input if not present in HTML
    const el = document.createElement("input");
    el.id = "binsInput";
    el.type = "number";
    el.value = "50";
    el.min = "2";
    document.getElementById("controls").appendChild(el);
    return el;
  })();

let controller = null;
let worker = null;
let chart = null;

// Histogram state
let binCount = 50;
let bins = null; // Int32Array
let minVal = Infinity;
let maxVal = -Infinity;
let totalCount = 0;

startBtn.addEventListener("click", start);
cancelBtn.addEventListener("click", cancel);

let histChart = null;
let cdfChart = null;

function initCharts() {
  const histCtx = document.getElementById("histCanvas").getContext("2d");
  const cdfCtx = document.getElementById("cdfCanvas").getContext("2d");

  if (histChart) histChart.destroy();
  if (cdfChart) cdfChart.destroy();

  histChart = new Chart(histCtx, {
    type: "bar",
    data: {
      labels: [],
      datasets: [{ label: "Histogram", data: [], backgroundColor: "#1976d2" }],
    },
    options: {
      animation: false,
      scales: {
        x: { title: { display: true, text: "Range" } },
        y: { title: { display: true, text: "Count" }, beginAtZero: true },
      },
    },
  });

  cdfChart = new Chart(cdfCtx, {
    type: "line",
    data: {
      labels: [],
      datasets: [
        {
          label: "Cumulative Distribution",
          data: [],
          borderColor: "#d32f2f",
          tension: 0.1,
        },
      ],
    },
    options: {
      animation: false,
      scales: {
        x: { title: { display: true, text: "Range" } },
        y: {
          title: { display: true, text: "Cumulative %" },
          beginAtZero: true,
          max: 100,
        },
      },
    },
  });
}

function start() {
  const file = fileInput.files && fileInput.files[0];
  if (!file) {
    statusEl.textContent = "Select a file first";
    return;
  }
  binCount = Math.max(2, parseInt(binsInput.value, 10) || 50);
  const batchSize = Math.max(1000, parseInt(batchSizeInput.value, 10) || 10000);

  initCharts();
  resetHistogramState(binCount);

  // Create worker via Blob to avoid file:// Worker CORS issues
  worker = createWorkerFromString(workerSource());
  worker.postMessage({ type: "config", batchSize });
  worker.onmessage = handleWorkerMessage;

  controller = new AbortController();
  const signal = controller.signal;
  const totalBytes = file.size;
  let processedBytes = 0;
  updateProgress(0);
  statusEl.textContent = "Streaming and building histogram...";
  startBtn.disabled = true;
  cancelBtn.disabled = false;

  const stream = file.stream().pipeThrough(new TextDecoderStream());
  const reader = stream.getReader();

  (async () => {
    try {
      while (true) {
        const { done, value } = await reader.read();
        if (done) break;
        processedBytes += value.length;
        updateProgress(processedBytes / totalBytes);
        worker.postMessage({ type: "chunk", text: value });
        await new Promise((r) => setTimeout(r, 0));
        if (signal.aborted) throw new Error("aborted");
      }
      worker.postMessage({ type: "end" });
    } catch (err) {
      if (err.message === "aborted") statusEl.textContent = "Cancelled";
      else {
        console.error(err);
        statusEl.textContent = "Error: " + err.message;
      }
      cleanup();
    }
  })();
}

function cancel() {
  if (controller) controller.abort();
  if (worker) worker.terminate();
  cleanup();
  statusEl.textContent = "Cancelled";
}

function cleanup() {
  startBtn.disabled = false;
  cancelBtn.disabled = true;
  updateProgress(0);
  controller = null;
  worker = null;
}

function handleWorkerMessage(ev) {
  const msg = ev.data;
  if (msg.type === "batch") {
    let numbers;
    if (msg.numbers instanceof ArrayBuffer) {
      numbers = Array.from(new Float64Array(msg.numbers));
    } else if (Array.isArray(msg.numbers)) {
      numbers = msg.numbers;
    } else {
      numbers = Array.from(msg.numbers || []);
    }
    processNumbersForHistogram(numbers);
  } else if (msg.type === "done") {
    statusEl.textContent = "Finished. Finalizing histogram...";
    renderCharts();
    cleanup();
    statusEl.textContent = "Completed";
  }
}

function resetHistogramState(binsN) {
  binCount = binsN;
  bins = new Int32Array(binCount);
  minVal = Infinity;
  maxVal = -Infinity;
  totalCount = 0;
  updateChartLabels();
}

function processNumbersForHistogram(numbers) {
  // Update min/max first
  let needRebin = false;
  let newMin = minVal,
    newMax = maxVal;
  for (const v of numbers) {
    if (!Number.isFinite(v)) continue;
    if (v < newMin) newMin = v;
    if (v > newMax) newMax = v;
  }
  if (newMin === Infinity) return; // no valid numbers in batch

  if (totalCount === 0) {
    // first data
    minVal = newMin;
    maxVal = newMax;
  } else {
    if (newMin < minVal || newMax > maxVal) {
      needRebin = true;
      const oldMin = minVal,
        oldMax = maxVal;
      minVal = Math.min(minVal, newMin);
      maxVal = Math.max(maxVal, newMax);
      // rebin existing counts into new bins
      bins = rebinCounts(bins, oldMin, oldMax, minVal, maxVal, binCount);
    }
  }

  // Now increment counts for this batch
  for (const v of numbers) {
    if (!Number.isFinite(v)) continue;
    const idx = valueToBinIndex(v, minVal, maxVal, binCount);
    bins[idx]++;
    totalCount++;
  }

  // Throttle chart updates
  scheduleChartUpdate();
}

let pendingUpdate = false;
function scheduleChartUpdate() {
  if (pendingUpdate) return;
  pendingUpdate = true;
  requestAnimationFrame(() => {
    pendingUpdate = false;
    renderCharts();
  });
}

function renderCharts() {
  if (totalCount === 0) {
    // niente dati ancora: mostra etichette vuote
    updateChartLabels();
    return;
  }

  const labels = [];
  const histData = [];
  const cdfData = [];

  let cumulative = 0;

  for (let i = 0; i < binCount; i++) {
    const [a, b] = binRange(i, minVal, maxVal, binCount);
    labels.push(`${a.toFixed(3)}–${b.toFixed(3)}`);

    const count = bins[i];
    histData.push(count);

    cumulative += count;
    cdfData.push((cumulative / totalCount) * 100);
  }

  if (histChart) {
    histChart.data.labels = labels;
    histChart.data.datasets[0].data = histData;
    histChart.update("none");
  }
  if (cdfChart) {
    cdfChart.data.labels = labels;
    cdfChart.data.datasets[0].data = cdfData;
    cdfChart.update("none");
  }
}

function valueToBinIndex(v, min, max, binsN) {
  if (v <= min) return 0;
  if (v >= max) return binsN - 1;
  const ratio = (v - min) / (max - min);
  return Math.min(binsN - 1, Math.floor(ratio * binsN));
}

function binRange(i, min, max, binsN) {
  const width = (max - min) / binsN;
  const a = min + i * width;
  const b = a + width;
  return [a, b];
}

function rebinCounts(oldCounts, oldMin, oldMax, newMin, newMax, binsN) {
  // Map old bin centers into new bins and accumulate counts
  const newCounts = new Int32Array(binsN);
  if (oldMin === Infinity || oldMax === -Infinity) return newCounts;
  const oldN = oldCounts.length;
  for (let i = 0; i < oldN; i++) {
    const center = oldMin + ((i + 0.5) * (oldMax - oldMin)) / oldN;
    const newIdx = valueToBinIndex(center, newMin, newMax, binsN);
    newCounts[newIdx] += oldCounts[i];
  }
  return newCounts;
}

function updateProgress(fraction) {
  const pct = Math.round(fraction * 100);
  progressFill.style.width = pct + "%";
  statusEl.textContent = `Processed ${pct}%`;
}

/* Worker creation via Blob to avoid file:// issues */
function createWorkerFromString(codeStr) {
  const blob = new Blob([codeStr], { type: "application/javascript" });
  return new Worker(URL.createObjectURL(blob));
}

/* Worker source string (same parsing worker as before) */
function workerSource() {
  return `
let batchSize = 10000;
let leftover = '';
self.onmessage = (ev) => {
  const msg = ev.data;
  if (msg.type === 'config') { batchSize = msg.batchSize || batchSize; return; }
  if (msg.type === 'chunk') { parseChunk(msg.text); return; }
  if (msg.type === 'end') { flushLeftover(); self.postMessage({ type: 'done' }); return; }
};
function parseChunk(text) { const combined = leftover + text; const tokens = combined.split(/[,\\n\\r]+/); leftover = tokens.pop() || ''; const out = []; for (let t of tokens) { if (!t) continue; const n = parseFloat(t.trim()); if (!Number.isNaN(n)) out.push(n); if (out.length >= batchSize) { const fa = new Float64Array(out); self.postMessage({ type: 'batch', numbers: fa.buffer }, [fa.buffer]); out.length = 0; } } if (out.length > 0) { const fa = new Float64Array(out); self.postMessage({ type: 'batch', numbers: fa.buffer }, [fa.buffer]); } } function flushLeftover() { if (leftover) { const n = parseFloat(leftover.trim()); if (!Number.isNaN(n)) { const fa = new Float64Array([n]); self.postMessage({ type: 'batch', numbers: fa.buffer }, [fa.buffer]); } leftover = ''; } }
function flushLeftover() {
  if (leftover) {
    const n = parseFloat(leftover.trim());
    if (!Number.isNaN(n)) {
      self.postMessage({ type: 'batch', numbers: [n] }, [floatArrayToTransfer([n])]);
    }
    leftover = '';
  }
}
function floatArrayToTransfer(arr) {
  const fa = new Float64Array(arr);
  return fa.buffer;
}
`;
}
