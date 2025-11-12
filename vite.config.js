import { defineConfig } from 'vite';

export default defineConfig({
  server: {
    fs: {
      allow: ['..'], // allow Vite to serve parent dirs like wasm/
    },
  },
});