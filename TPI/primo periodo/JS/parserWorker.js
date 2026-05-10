// parserWorker.js
// Receives messages: { type: 'config', batchSize: number } or { type: 'chunk', text: string } or { type: 'end' }
// Posts messages: { type: 'batch', numbers: Float64Array } and { type: 'done' }

let batchSize = 10000;
let leftover = "";

self.onmessage = (ev) => {
  const msg = ev.data;
  if (msg.type === "config") {
    batchSize = msg.batchSize || batchSize;
    return;
  }
  if (msg.type === "chunk") {
    parseChunk(msg.text);
    return;
  }
  if (msg.type === "end") {
    flushLeftover();
    self.postMessage({ type: "done" });
    return;
  }
};

function parseChunk(text) {
  // Prepend leftover from previous chunk
  const combined = leftover + text;
  // Split on commas and newlines
  const tokens = combined.split(/[\n\r,]+/);
  // Last token may be incomplete — keep it as leftover
  leftover = tokens.pop() || "";

  const out = [];
  for (let t of tokens) {
    if (!t) continue;
    const n = parseFloat(t.trim());
    if (!Number.isNaN(n)) out.push(n);
    // If out reaches batchSize, send it
    if (out.length >= batchSize) {
      self.postMessage({ type: "batch", numbers: out }, [
        floatArrayToTransfer(out),
      ]);
      out.length = 0;
    }
  }
  // send remaining if any (but not necessarily full batch)
  if (out.length > 0) {
    self.postMessage({ type: "batch", numbers: out }, [
      floatArrayToTransfer(out),
    ]);
  }
}

function flushLeftover() {
  if (leftover) {
    const n = parseFloat(leftover.trim());
    if (!Number.isNaN(n)) {
      self.postMessage({ type: "batch", numbers: [n] }, [
        floatArrayToTransfer([n]),
      ]);
    }
    leftover = "";
  }
}

// Helper to convert JS array to transferable Float64Array buffer
function floatArrayToTransfer(arr) {
  const fa = new Float64Array(arr);
  return fa.buffer;
}
