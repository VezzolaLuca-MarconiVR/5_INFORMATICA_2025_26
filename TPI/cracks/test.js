const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

// The absolute MAX and MIN value for the random numbers generated
const RANDOM_GEN_RANGE = 5;
const GRAPH_SCALE = 10;

function main(lenA, lenB) {
  drawTwoGraphsDTW(ctx, generateRandos(lenA), generateRandos(lenB));
}

function generateRandos(len) {
  let randos = new Array(len);

  // Randos will range from -RANDOM_GEN_RANGE to RANDOM_GEN_RANGE
  for (let i = 0; i < len; i++) {
    randos[i] =
      Math.floor(Math.random() * (RANDOM_GEN_RANGE * 2 + 1)) - RANDOM_GEN_RANGE;
  }

  return randos;
}

function drawLine(ctx, points) {
  // HOW TO DRAW A LINE:
  // ctx.beginPath(); // Initialize path
  // ctx.moveTo(x1, y1); // Move to origin of the path
  // ctx.lineTo(x2, y2); // "Draw" a line from (x1;y1) to (x2;y2)
  // ctx.stroke(); // Actually render the line

  ctx.beginPath();
  ctx.moveTo(0, points[0]);

  points.forEach((element, index) => {
    if (index != 0) ctx.lineTo(index * GRAPH_SCALE, element);
    ctx.stroke();
  });
}

function drawTwoGraphsDTW(ctx, datasetA, datasetB) {
  // Finding the top and bottom bounds of the datasets
  const maxA = arrayMax(datasetA);
  const maxB = arrayMax(datasetB);

  const graphsPadding = 20;

  // Calculate the DTW

  // Shifting the graphs so that the first is on the left-top corner, and the second is
  // under it and the two are separated by a padding of length "graphsPadding".
  const graphA = datasetA.map(
    (element) => Math.abs(element - maxA) * GRAPH_SCALE,
  );

  // Calculate lowest point of first graph (the furthest down)
  const lowestPointOfGraphA = arrayMax(datasetA);

  const graphB = datasetB.map(
    (element) =>
      Math.abs(element - maxB) * GRAPH_SCALE +
      lowestPointOfGraphA +
      graphsPadding,
  );

  // Drawing the graphs
  drawLine(ctx, graphA);
  drawLine(ctx, graphB);

  // Drawing the DTW connections
}

// function arrayMin(arr) {
//   let min = Infinity;
//   for (let i = 0; i < arr.length; i++) if (arr[i] < min) min = arr[i];
//   return min;
// }

function arrayMax(arr) {
  let max = 0;
  for (let i = 0; i < arr.length; i++) if (arr[i] > max) max = arr[i];
  return max;
}
