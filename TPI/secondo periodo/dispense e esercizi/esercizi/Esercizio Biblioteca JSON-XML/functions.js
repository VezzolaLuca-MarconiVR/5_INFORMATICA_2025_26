// File manipulation module
const fs = require('fs').promises;
// Used for random UUID
const crypto = require('crypto');

// Factory function to create a new book element
const createBook = (values = {}) => ({
  id: values.id ?? crypto.randomUUID(), // Fallbacks to a randomly generated id
  title: values.title ?? "--Untitled--",
  author: values.author ?? "--Unknown--",
  year: values.year ?? null,
  genre: values.genre ?? "General"
});
// Createing books with the factory function:
// const dict1 = createBook({ key1: "A", key2: "B", key3: "C" });
// const dict2 = createBook({ key1: "X" }); // Others use defaults

async function upload_json(filePath) {
  try {
    const data = await fs.readFile(filePath, 'utf8');
    const library = JSON.parse(data).library;
    console.log("Loaded library:", library);
    return library;
  } catch (err) {
    console.error("Error reading JSON:", err);
    return [];
  }
}

async function save_json(books, filePath) {
  try {
    const json = JSON.stringify({ library: books }, null, 2);
    await fs.writeFile(filePath, json);
    console.log("JSON saved successfully!");
  } catch (err) {
    console.error("Error writing JSON:", err);
  }
}

// MAIN EXECUTION
async function main() {
  const jsonLibrary = await upload_json('./data/library.json');
  await save_json(jsonLibrary, './data/newLibrary.json');
}

main();