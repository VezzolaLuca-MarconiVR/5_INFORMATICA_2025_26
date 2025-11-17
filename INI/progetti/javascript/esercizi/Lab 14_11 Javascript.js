/*
creare le funzioni lambda, con i commenti:
    1. somma, riceve un array e restituisce la somma degli elementi
    2. concatena, riceve un array di stringhe e le concatena 
    3. cerca, riceve una stringa e dice se sono presenti caratteri non dell'alfabeto
    4. fattoriale
*/

const somma = (a, b) => a+b;
const concatena = (arr) => {
    arr.reduce((total, el) => total+el);
}