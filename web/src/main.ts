import './style.css';

// @ts-ignore — Emscripten JS has no types
import initModule from './wasm_loader.js';

async function init() {
  const Module = await initModule();

  // Wrap C++ functions (use actual exported names from C++)
  const add = Module.cwrap('add', 'number', ['number', 'number']);
  const subtract = Module.cwrap('subtract', 'number', ['number', 'number']);
  const multiply = Module.cwrap('multiply', 'number', ['number', 'number']);
  const divide = Module.cwrap('divide', 'number', ['number', 'number']);
  const sin_deg = Module.cwrap('sin_deg', 'number', ['number']);
  const cos_deg = Module.cwrap('cos_deg', 'number', ['number']);
  const tan_deg = Module.cwrap('tan_deg', 'number', ['number']);

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
  const getVal = (id: string) => parseFloat((document.getElementById(id) as HTMLInputElement).value);

  document.querySelectorAll<HTMLButtonElement>('button').forEach(btn => {
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
      result.textContent = `Result: ${res}`;
    };
  });
}

init();

