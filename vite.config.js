import { defineConfig } from 'vite';

export default defineConfig({
   root: './platforms/web',
  server: {
    fs: {
      allow: ['..'], // allow Vite to serve parent dirs like wasm/
    },
  },
});