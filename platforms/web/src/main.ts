import './style.css';

// @ts-ignore
import createCalculatorModule from '../../../build/calculator.js';

async function main() {

  const Calculator = await createCalculatorModule({
  locateFile: (path:string) =>
    path.endsWith('.wasm')
      ? new URL(`../../../build/${path}`, import.meta.url).href
      : path,
});

function startOperationStressTest() {
  console.log("Starting WASM operation stress test...");

  let count = 0;
 const operations = [
    { fn: add, name: "add" },
    { fn: subtract, name: "subtract" },
    { fn: multiply, name: "multiply" },
    { fn: divide, name: "divide" }
  ];
  const interval = setInterval(() => {
    const a = Math.random() * 10000 * performance.now();
    const b = Math.random() * 10000 * performance.now();

    const op = operations[Math.floor(Math.random() * operations.length)];

    try {
     const result = op.fn(a, b);
      
      // print every 1000th operation
      if (count % 1000 === 0) {
        console.log(`Iter: ${count},op=${op.name}, a=${a.toFixed(2)}, b=${b.toFixed(2)}, result=${result}`);
      }

      count++;
    } catch (err) {
      console.error("Error during stress test:", err);
      clearInterval(interval);
    }

    // Stop after 100k operations
    if (count >= 10000) {
      console.log("Stress test complete.");
      clearInterval(interval);
    }
  }, 0);
}
  const add = Calculator.cwrap('add', 'number', ['number', 'number']);
  const subtract = Calculator.cwrap('subtract', 'number', ['number', 'number']);
  const multiply = Calculator.cwrap('multiply', 'number', ['number', 'number']);
  const divide = Calculator.cwrap('divide', 'number', ['number', 'number']);
  const sin_deg = Calculator.cwrap('sin_deg', 'number', ['number']);
  const cos_deg = Calculator.cwrap('cos_deg', 'number', ['number']);
  const tan_deg = Calculator.cwrap('tan_deg', 'number', ['number']);

  const app = document.querySelector<HTMLDivElement>('#app')!;
  app.innerHTML = `
    <div class="calc">
      <h1>Scientific Calculator</h1>
      <input id="a" placeholder="Enter A" type="number" />
      <input id="b" placeholder="Enter B" type="number" />
      <div class="buttons">
        <button data-op="add">+</button>
        <button data-op="subtract">-</button>
        <button data-op="multiply">*</button>
        <button data-op="divide">/</button>
  
      </div>

      <button id="Test" style="margin-top: 20px; background: red; color: white;">
         Start Stress Test
      </button>

      <p id="result">Result: </p>
    </div>
`;
 
  const result = document.getElementById('result')!;
  const getVal = (id: string) =>
    parseFloat((document.getElementById(id) as HTMLInputElement).value);

  document.querySelectorAll<HTMLButtonElement>('button').forEach((btn) => {
    btn.onclick = () => {
      const op = btn.dataset.op!;
      const a = getVal('a');
      const b = getVal('b');
      let res: number;

      switch (op) {
        case 'add': res = add(a, b); break;
        case 'subtract': res = subtract(a, b); break;
        case 'multiply': res = multiply(a, b); break;
        case 'divide': res = divide(a, b); break;
        case 'sin_deg': res = sin_deg(a); break;
        case 'cos_deg': res = cos_deg(a); break;
        case 'tan_deg': res = tan_deg(a); break;
        default: res = NaN;
      }
      if (Math.abs(res - Math.round(res)) < 0.001) {
      res = Math.round(res);
    }
      result.textContent = `Result: ${res}`;
    };
  });

  document.getElementById("Test")!.onclick = () => {
    startOperationStressTest();
  };
}
main();

