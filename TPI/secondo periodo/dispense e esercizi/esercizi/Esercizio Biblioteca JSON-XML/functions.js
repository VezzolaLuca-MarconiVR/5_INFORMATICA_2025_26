// File manipulation module
const fs = require('fs').promises;
// Xml parser
const xml2js = require("xml2js");
// Used for random UUID
const crypto = require('crypto');
// Cmd input/output
const readline = require('node:readline');
// Personal colored console overrides
require("./coloredConsole.js");

// Factory function to create a new book element
function createBook(values = {}) {
  return ({
    id: values.id ?? crypto.randomUUID(), // Fallbacks to a randomly generated id
    title: values.title ?? "--Untitled--",
    author: values.author ?? "--Unknown--",
    year: values.year ?? null,
    genre: values.genre ?? "--Undefined--"
  });
}

async function upload_json(filePath) {
  try {
    const jsonText = await fs.readFile(filePath, 'utf8');
    const library = JSON.parse(jsonText).library;
    console.success("File uploaded successfully!");
    return library;
  } catch (err) {
    console.error("Error reading JSON:", err);
    return [];
  }
}

async function upload_xml(filePath) {
  try {
    const xmlText = await fs.readFile(filePath, 'utf8');
    const parser = new xml2js.Parser();
    const library = await parser.parseStringPromise(xmlText);
    xmlObj = xmlObj.library.book.map(b => ({
            id: b.$?.id,
            title: b.title?.[0],
            author: b.author?.[0],
            year: b.year?.[0],
            genre: b.genre?.[0]
          }));

    console.success("File uploaded successfully!");
    return xmlObj;
  } catch (err) {
    console.error("Error reading XML:", err);
    return [];
  }
}

async function save_json(library, filePath) {
  try {
    const json = JSON.stringify({ library: library }, null, 2);
    await fs.writeFile(filePath, json);
    console.success("JSON saved successfully!");
  } catch (err) {
    console.error("Error writing JSON:", err);
  }
}

async function save_xml(library, filepath) {
  try {
    const builder = new xml2js.Builder();

    // Convert the library array into an XML-friendly structure
    const xmlObj = {
      library: {
        book: library.map(b => ({
          $: { id: b.id },
          title: [b.title],
          author: [b.author],
          year: [b.year],
          genre: [b.genre]
        }))
      }
    };

    // Build XML text from the object
    const xmlText = builder.buildObject(xmlObj);

    // Write the XML string to the file
    await fs.writeFile(filepath, xmlText);

    console.success("XML saved successfully!");
  } catch (err) {
    console.error("Error in writing XML:", err);
  }
}

// Cmd input/output interface
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Function to ask user a number - returns parsed (type Number) user input (or NaN if invalid or null if empty)
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
  return library.filter(element => {
    return element['title'].includes(searchStr) || element['author'].includes(searchStr);
  });
}

// Get the index of the book with the specified id or -1 if the element is not found
function indexOfBook(library, id) {
  for (let i=0; i<library.length; i++) {
    if (library[i]['id'] == id) {
      return i;
    }
  }
  return -1;
}

// MAIN EXECUTION
async function main() {
  let library = new Array();
  
  // Options menu
  const menu = "====== MENU ======\n1. Upload from XML\n2. Upload from JSON\n3. Save in XML\n4. Save in JSON\n5. Add a book\n6. Find book\n7. Remove book\n8. Convert XML to JSON\n9. Convert JSON to XML\n10. Show the whole library\n0. Quit";
  
  let selectedMenuOption = -1;

  // Loop until user types '0' (quit)
  while(selectedMenuOption != 0){  
    // Print menu and wait for user selection
    selectedMenuOption = await askUserNumber(menu);

    // Good user input - proceeding with selected option
    switch(selectedMenuOption) {
      case 0:
        // Do option 0 - Quit (do nothing)
        break;
      case 1:{
        // Do option 1 - Upload XML
        let confirmed = true;

        if(library.length > 0) {
          // show warning
          console.warn("Warning: uploading a file will overwrite all of the data already uploaded and/or added manually.");

          confirmed = undefined;
          let userInput = (await askUserQuestion("Are you sure you want to continue? (Y/N)")).toUpperCase();
          while (confirmed === undefined) {
            if (userInput === "Y") {
              confirmed = true;
            } else if (userInput === "N") {
              confirmed = false;
            } else {
              userInput = (await askUserQuestion("Please type either 'Y' (yes) or 'N' (no).")).toUpperCase();
            }
          }
        }
        
        if (confirmed) {
          // ask for path once, then upload
          const path = await askUserQuestion("Type the path of the XML file to upload:");
          library = await upload_xml(path);
        }
        break;}
      case 2:{
        // Do option 2 - Upload JSON

        // ask and validate Y/N (case-insensitive)
        let confirmed = true;

        if(library.length > 0) {
          // show warning
          console.warn("Warning: uploading a file will overwrite all of the data already uploaded and/or added manually.");

          confirmed = undefined;
          let userInput = (await askUserQuestion("Are you sure you want to continue? (Y/N)")).toUpperCase();
          while (confirmed === undefined) {
            if (userInput === "Y") {
              confirmed = true;
            } else if (userInput === "N") {
              confirmed = false;
            } else {
              userInput = (await askUserQuestion("Please type either 'Y' (yes) or 'N' (no).")).toUpperCase();
            }
          }
        }
        
        if (confirmed) {
          // ask for path, then upload
          const path = await askUserQuestion("Type the path of the JSON file to upload:");
          library = await upload_json(path);
        }
      
        break;}
      case 3:
        // Do option 3 - Save XML
        save_xml(library, await askUserQuestion("Type the path where you want to save the file:"));
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
          console.success("Matches:",matches);
        } else {
          // No match found
          console.error("\nNo match found\n");
        }
        break;
      case 7:
        // Do option 7 - Remove book
        // Ask user which id has book to remove
        const userInput = await askUserQuestion("Type the id of the book you want to remove:");
        const idx = indexOfBook(library, userInput);
        
        console.debug("idx", idx);

        if(idx < 0){
          // No book found
          console.error("No book found with the id", userInput);
        } else {
          // Book found: display the book and ask for confirmation
          let confirmed = undefined;
          console.warn("Book to delete:", library[idx]);
          let userInput = (await askUserQuestion("Are you sure you want to delete this book? (Y/N)")).toUpperCase();
          while (confirmed === undefined) {
            if (userInput === "Y") {
              confirmed = true;
            } else if (userInput === "N") {
              confirmed = false;
            } else {
              userInput = (await askUserQuestion("Please type either 'Y' (yes) or 'N' (no).")).toUpperCase();
            }
          }
          if(confirmed) {
            library.splice(idx, 1);
            console.success("Book successfully deleted.");
          }
        }

        break;
      case 8:{ // Brackets make this a different block from the next, so 'tempLib' can be used independently
        // Do option 8 - Convert XML into JSON
        console.warn("This operation will not overwrite nor upload any data in the current application.");

        // Read XML file
        const tempLib = await upload_xml(await askUserQuestion("Type the path of the XML file to convert:"));

        // Write JSON file
        await save_json(tempLib, await askUserQuestion("Type the path where you want to save the JSON converted file:"));
        break;}
      case 9:{ // Brackets make this a different block from the previous, so 'tempLib' can be used independently
        // Do option 9 - Convert JSON into XML
        console.warn("This operation will not overwrite nor upload any data in the current application.");

        // Read JSON file
        const tempLib = await upload_json(await askUserQuestion("Type the path of the JSON file to convert:"));

        // Write XML file
        await save_xml(tempLib, await askUserQuestion("Type the path where you want to save the XML converted file:"));
        break;}
      case 10:
        // Do option 10 - Show all books
        console.success("Current library:", library);
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