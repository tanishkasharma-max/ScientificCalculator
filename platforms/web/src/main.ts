import './style.css';
import Chart from 'chart.js/auto';

// @ts-ignore
import createCalculatorModule from '../../../build/calculator.js';

async function main() {
  const Calculator = await createCalculatorModule({
    locateFile: (path: string) =>
      path.endsWith('.wasm')
        ? new URL(`../../../build/${path}`, import.meta.url).href
        : path,
  });


  const app = document.querySelector<HTMLDivElement>('#app')!;
  app.innerHTML = `
    <h1>Scientific Calculator + WASM Memory Test</h1>

    <div class="calc">
      <input id="a" placeholder="Enter A" type="number" />
      <input id="b" placeholder="Enter B" type="number" />
      <div class="buttons">
        <button data-op="add">+</button>
        <button data-op="subtract">-</button>
        <button data-op="multiply">*</button>
        <button data-op="divide">/</button>
      </div>
      <p id="result">Result: </p>
    </div>

    <h2>WASM Memory Usage</h2>
    <canvas id="memChart" width="600" height="200"></canvas>
  `;


  const canvas = document.getElementById("memChart") as HTMLCanvasElement;
  const ctx = canvas.getContext("2d")!;
  const data = {
    labels: [] as string[],
    datasets: [
      {
        label: "WASM Memory Usage (MB)",
        data: [] as number[],
        borderColor: "rgba(75,192,192,1)",
        tension: 0.3,
      },
    ],
  };
  const memChart = new Chart(ctx, {
    type: "line",
    data,
    options: { animation: false },
  });

  function getWasmMemMB() {
    return Calculator._getMemoryUsage ? Calculator._getMemoryUsage() / (1024 * 1024) : 0;
  }

  setInterval(() => {
    const now = new Date().toLocaleTimeString();
    data.labels.push(now);
    data.datasets[0].data.push(getWasmMemMB());

    if (data.labels.length > 30) {
      data.labels.shift();
      data.datasets[0].data.shift();
    }

    memChart.update();
  }, 1000);


  const add = Calculator.cwrap("add", "number", ["number", "number"]);
  const subtract = Calculator.cwrap("subtract", "number", ["number", "number"]);
  const multiply = Calculator.cwrap("multiply", "number", ["number", "number"]);
  const divide = Calculator.cwrap("divide", "number", ["number", "number"]);


  const resultEl = document.getElementById("result")!;
  const getVal = (id: string) => parseFloat((document.getElementById(id) as HTMLInputElement).value);

  document.querySelectorAll<HTMLButtonElement>("button").forEach((btn) => {
    btn.onclick = () => {
      const op = btn.dataset.op!;
      const a = getVal("a");
      const b = getVal("b");
      let res: number;

      switch (op) {
        case "add": res = add(a, b); break;
        case "subtract": res = subtract(a, b); break;
        case "multiply": res = multiply(a, b); break;
        case "divide": res = divide(a, b); break;
        default: res = NaN;
      }

      if (Math.abs(res - Math.round(res)) < 0.001) {
        res = Math.round(res);
      }

      resultEl.textContent = `Result: ${res}`;
    };
  });

  const ops = [
    { name: "add", fn: add },
    { name: "subtract", fn: subtract },
    { name: "multiply", fn: multiply },
    { name: "divide", fn: divide },
  ];

  setInterval(() => {
    const a = Math.random() * 1000 * performance.now();
    const b = Math.random() * 1000 * performance.now();
    const op = ops[Math.floor(Math.random() * ops.length)];
    const safeB = op.name === "divide" && b === 0 ? 1 : b;
    const res = op.fn(a, safeB);

    console.log(
      `%c[WASM OP] ${op.name} → a=${a.toFixed(2)}, b=${safeB.toFixed(2)}, result=${res.toFixed(2)}`,
      "color:#00c853;font-weight:bold"
    );
  }, 500);
}

main();
