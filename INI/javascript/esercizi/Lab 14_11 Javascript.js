/*
Consegna: creare le funzioni lambda, con i commenti:
    1. somma, riceve un array e restituisce la somma degli elementi
    2. concatena, riceve un array di stringhe e le concatena 
    3. cerca, riceve una stringa e dice se sono presenti caratteri non dell'alfabeto
    4. fattoriale
*/

// Somma, riceve un array e restituisce la somma degli elementi
const somma = (a, b) => a + b;

// Concatena, riceve un array di stringhe e le concatena
const concatena = (strArr) =>
  /*
  Metodi degli array in JS ==> https://www.w3schools.com/jsref/jsref_array[].asp
  
  Array.prototype.reduce() method:
  esegue una funzione di callback riduttore su
  ciascun elemento di un array, in ordine, accumulando un singolo valore dall'array.

  Cos'è una funzione di callback?
  Una funzione di callback in JavaScript è una funzione passata come argomento a un'altra funzione, che viene poi richiamata all'interno della funzione esterna per completare un'attività o una routine specifica.
  Questo meccanismo consente di controllare l'ordine di esecuzione, in particolare per operazioni asincrone come il recupero di dati, la gestione di eventi o l'impostazione di timer.
  I callback sono essenziali per il codice non bloccante, consentendo a JavaScript di eseguire altre attività in attesa del completamento di operazioni come richieste di rete o lettura di file.
  Sono comunemente utilizzati nelle funzioni di ordine superiore, in cui il callback viene eseguito dopo che la funzione primaria ha terminato il suo compito, immediatamente (sincrono) o dopo un ritardo o un evento (asincrono).
  */
  strArr.reduce((totale, el) => totale + el);
// Cerca, riceve una stringa e dice se sono presenti caratteri non dell'alfabeto
const cerca = (str) =>
  /*
    RegExp method test:
    The test() method tests for a match in a string.
    If it finds a match, it returns true, otherwise it returns false.

    Syntax:
      regexp.test(string)

    Cos'è una Regular Expression (abbr. RegExp)?
    Syntax:
      /pattern/modifier flags

    ^ ==> 	Matches all characters NOT between the brackets

    fonte: https://www.w3schools.com/js/js_regexp.asp
  */
  /[^a-z|A-Z]/.test(str) ? "si" : "no";
// Fattoriale
const fattoriale = (n) => {
  let fact = 2;
  while (n > 2) fact *= n--;
  return fact;
};

function main(a, b, strArr, str, n) {
  // Ho utilizzato i "Template literals" per poter scrivere codice nella stringa
  // I Template literals sono delimitati da backtick (`) e il codice è incapsulato con "${,...}"

  console.log(`Somma di ${a} e ${b}: ${somma(a, b)}`);

  console.log(`Concatenatura di ${strArr}: ${concatena(strArr)}`);

  console.log(`Trovato un carattere non-lettera in ${str}: ${cerca(str)}`);

  console.log(`Fattoriale di ${n}: ${fattoriale(n)}`);
}
