import './style.css';

// @ts-ignore
import createCalculatorModule from '../../../build/calculator.js';

async function main() {

  const Calculator = await createCalculatorModule({
  locateFile: (path) =>
    path.endsWith('.wasm')
      ? new URL(`../../../build/${path}`, import.meta.url).href
      : path,
});


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
      <input id="b" placeholder="Enter B (optional)" type="number" />
      <div class="buttons">
        <button data-op="add">+</button>
        <button data-op="subtract">-</button>
        <button data-op="multiply">*</button>
        <button data-op="divide">/</button>
        <button data-op="sin_deg">sin</button>
        <button data-op="cos_deg">cos</button>
        <button data-op="tan_deg">tan</button>
      </div>
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
}
main();

