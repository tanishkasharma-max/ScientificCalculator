// Re-export the root wasm loader so bundlers can import a local file.
// This avoids bundlers rejecting imports that reference files outside the source tree.
export { default } from '../../wasm/calculator.js';
