function main(divisions, data) {
  const analisis = analize(divisions, data);
  drawChart(analisis);
}

function analize(divisions, data) {
  let analisis = new Array(divisions);

  // Riordina i dati in ordine decrescente
  data.sort((a, b) => a - b);

  let min = data[0];
  let max = data[data.length - 1];

  let divisionRange = (max - min) / divisions;

  let startIndex = 0;
  let count;

  for (let d = 0; d < divisions; d++) {
    count = 0;

    for (
      let i = startIndex;
      i < data.length && data[i] < min + (d + 1) * divisionRange;
      i++
    ) {
      count++;
    }

    startIndex += count;

    if (startIndex >= data.length) {
      startIndex = data.length;
    }

    analisis[d] = count;
  }

  return analisis;
}

function drawChart(values) {
  const ctx = document.getElementById("chart").getContext("2d");
  new Chart(ctx, {
    type: "bar",
    data: {
      labels: values.map((_, i) => "Div " + (i + 1)),
      datasets: [
        {
          label: "Distribuzione",
          data: values,
          backgroundColor: "rgba(54, 162, 235, 0.6)",
          borderColor: "rgba(54, 162, 235, 1)",
          borderWidth: 1,
        },
      ],
    },
    options: { scales: { y: { beginAtZero: true } } },
  });
}
