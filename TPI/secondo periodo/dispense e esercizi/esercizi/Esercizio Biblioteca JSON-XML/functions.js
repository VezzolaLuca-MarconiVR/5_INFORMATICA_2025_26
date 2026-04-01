// File manipulation module
const fs = require('fs').promises;
// Used for random UUID
const crypto = require('crypto');
// Cmd input/output
const readline = require('node:readline');
// Cmd colors
const chalk = require('chalk');

// Chalk-colored console modes
function console.log(str) {
  
}

// Factory function to create a new book element
const createBook = (values = {}) => ({
  id: values.id ?? crypto.randomUUID(), // Fallbacks to a randomly generated id
  title: values.title ?? "--Untitled--",
  author: values.author ?? "--Unknown--",
  year: values.year ?? null,
  genre: values.genre ?? "General"
});

async function upload_json(filePath) {
  try {
    const data = await fs.readFile(filePath, 'utf8');
    const library = JSON.parse(data).library;
    console.log("\n<<<<< File uploaded successfully! >>>>>\n");
    return library;
  } catch (err) {
    console.error("Error reading JSON:", err);
    return [];
  }
}

async function save_json(library, filePath) {
  try {
    const json = JSON.stringify({ library: library }, null, 2);
    await fs.writeFile(filePath, json);
    console.log("\n<<<<< JSON saved successfully! >>>>>\n");
  } catch (err) {
    console.error("Error writing JSON:", err);
  }
}

// Cmd input/output interface
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Function to ask user a number - returns parsed user input (Number or NaN or null if empty)
function askUserNumber(message) {
  return new Promise(resolve => {
    rl.question(message + "\n> ", answer => {
      if (answer.trim() === "") {
        resolve(null); // empty input
      } else {
        resolve(Number(answer));
      }
    });
  });
}

// Function to ask user a question - returns the trimmed user input as string
function askUserQuestion(message) {
  return new Promise(resolve => {
    rl.question(message + "\n", answer => {
      resolve(answer.trim());
    })
  })
}

// Search for partial or full matches in the title and author values of a list of books - if none found, return empty list
function findMatchesInLibrary(library, searchStr) {
  return library.filter(element => {element['title'].includes(searchStr) || element['author'].includes(searchStr)});
}

// Get the index of the book with the specified id or undefined if the element is not found
function indexOfBook(library, id) {
  return library.indexOf(element => { element['id'] == id});
}

// MAIN EXECUTION
async function main() {
  let library = new Array();
  
  // Options menu
  const menu = "====== MENU ======\n1. Carica da XML\n2. Carica da JSON\n3. Salva in XML\n4. Salva in JSON\n5. Aggiungi libro\n6. Cerca libro\n7. Rimuovi libro\n8. Converti XML → JSON\n9. Converti JSON → XML\n10. Mostra tutti i libri\n0. Esci";
  
  let selectedMenuOption = -1;

  let userInput;

  // Clear console (if possible)
  console.clear();

  // Loop until user types '0' (quit)
  while(selectedMenuOption != 0){  
    // Print menu and wait for user selection
    selectedMenuOption = await askUserNumber(menu);

    // Good user input - proceeding with selected option
    switch(selectedMenuOption) {
      case 0:
        // Do option 0 - Quit (do nothing)
        break;
      case 1:
        // Do option 1 - Upload XML
        break;
      case 2:
        // Do option 2 - Upload JSON
        library = library.concat(await upload_json(await askUserQuestion("Type the path of the JSON file to upload:")));
        break;
      case 3:
        // Do option 3 - Save XML3
        break;
      case 4:
        // Do option 4 - Save JSON
        save_json(library, await askUserQuestion("Type the path where you want to save the file:"));
        break;
      case 5:
        // Do option 5 - Add book
        const id = await askUserNumber("Type the book id (blank or a NaN to generate a random UUID): ");
        const title = await askUserQuestion("Type the title of the book: ");
        const author = await askUserQuestion("Type the author of the book: ");
        const year = await askUserQuestion("Type the year of publication of the book: ");
        const genre = await askUserQuestion("Type the genre of the book: ");

        if (id == null | isNaN(id)){
          library.push(createBook({title:title, author:author, year:year, genre:genre}));
        } else {
          library.push(createBook({id:id, title:title, author:author, year:year, genre:genre}));
        }
        break;
      case 6:
        // Do option 6 - Find book (by title and/or author)
        const searchStr = await askUserQuestion("Type the title or author (also partially): ");
        const matches = findMatchesInLibrary(library, searchStr);
        if (Array.isArray(matches) && matches.length > 0){
          // Matches found
          console.log();
        } else {
          // No match found
          console.log("No ");
        }
        break;
      case 7:
        // Do option 7 - Remove book

        break;
      case 8:
        // Do option 8 - Convert XML into JSON
        break;
      case 9:
        // Do option 9 - Convert JSON into XML
        break;
      case 10:
        // Do option 10 - Show all books
        console.log("\nCurrent library:\n", library);
        break;
      default:
        // Bad user input
        console.error("\nError: invalid user input. Please only type numbers between 0 and 10.\n");
        break;
    }
  }
  rl.close();
}

main();