### **_Vezzola Luca - 5CI - anno scolastico 2025/26_**

# **LABORATORIO DI INFORMATICA**

#### 16 settembre 2025

### Nome Software House:

Primrose _(primrose (inglese) -> primula)_.

### Nome Piattaforma:

Ekhoikos _(ekho (greco) -> rumore; oikos (latino) -> casa, ambiente)_.

### Descrizione del progetto:

- Sistema di compravendita online di beni fisici e digitali fatti a mano, per promuovere i liberi professionisti ed il self-made.
- Sulla piattaforma si promuove un'economia a km zero, basando la ricerca sulla distanza minima tra cliente-"artigiano" e la sostenibilità dei materiali utilizzati.
- Gli obbiettivi della piattaforma sono i seguenti:
  - Creare un ecosistema di e-commerce per prodotti creati e lavorati a mano, sia fisici che digitali
  - Per limitare i consumi e le emissioni, la ricerca dei prodotti punta a mostrare gli "artigiani" più vicini, promuovendo così anche la cultura locale.
  - Per favorire l'utilizzo di materiali ecosostenibili nei prodotti fisici esiste un sistema di classifica basata sulle recensioni degli acquirenti.
  - Per ogni vendita, il 5% del ricavato viene donato ad una o più associazioni scelte dall'acquirente al momento dell'acquisto.

### Definizione del target

Ekhoikos è stato pensato per chiunque abbia interesse ad acquistare prodotti ecosostenibili e soprattutto locali, a sostenere gli artisti e la cultura locali.

Gli utilizzatori saranno persone dai 18 ai 50 anni.

Esempio di target:

- Personas ==> Roberta
- Target ==> Cittadina Ecologista
- Caratteristiche ==> E' una signora di 47 anni con una passione per le decorazioni in legno intagliato.

---

#### 23 settembre 2025

### Mockup progetto (fatto con [Whimsical](https://whimsical.com/)):

![shop and chat mockups](img/MOCKUP.png "shop and chat mockups")

### Consigli della prof:

- Aggiungere una pagina di sensibilizzazione sulle emissioni di CO2 dovute ai trasporti e le enormi distanze che questi percorrono prima di arrivare a noi.

---

#### 28 settembre 2025

### Mockup Homepage:

![homepage mockup](img/homepage_MOCKUP.png "homepage mockup")

---

#### 30 settembre 2025

### Studio per l'implementazione di React:

Apprendimento in autonomia della libreria JavaScript React, assieme a Vite - un server di sviluppo back-end locale -, e Bootstrap - un\* libreria/framework/toolkit (non si sanno definire nemmeno loro) - per sviluppare meglio, e più velocemente, il front-end.

#### Sitografia:

- [video-spiegazione: introduzione a React](https://youtu.be/SqcY0GlETPk?si=3CgvXV8WVLR5Bxap)
- [video-spiegazione: modificare i colori di Bootstrap](https://www.youtube.com/watch?v=au5ccstcbnc)

### Nota:

## Non utilizzerò Bootstrap. E' troppo rigido per ciò che voglio creare. Piuttosto scrivo il CSS manualmente per avere più libertà nello stile e nella forma.

---

#### 2 Ottobre 2025

### Creazione di una sezione riservata ad educazione civica nell'index del sito

Creazione di una sezione nella parte finale dell'index seguendo i [consigli dati dalla prof](#consigli-della-prof).

---

#### 19 Ottobre 2025

### Inizio implementazione in React

Implementazione in React dei component base (App, Navbar, Home); esplorato React Bits e trovato due elementi interessanti:

- [sfondo-prisma](https://reactbits.dev/backgrounds/prism)
- [navbar-dock](https://reactbits.dev/components/dock)

#### Sitografia:

- [album-spiegazione: introduzione a React](https://www.youtube.com/playlist?list=PL4cUxeGkcC9gZD-Tvwfod2gaISzfRiP9d)

---

#### 31 Ottobre 2025

### Continuazione implementazione in React

Implementazione in React del Dock (in sostituzione alla navbar) e trasposizione della home

#### Sitografia:

- [icone per react (già incluse)](https://react-icons.github.io/react-icons/)

---

#### 24 Novembre 2025

### Esercizi in JavaScript

Creare le funzioni lambda, con i commenti:

1. somma, riceve un array e restituisce la somma degli elementi
2. concatena, riceve un array di stringhe e le concatena
3. cerca, riceve una stringa e dice se sono presenti caratteri non dell'alfabeto
4. fattoriale

#### Esercizio svolto:

```js
// Somma, riceve un array e restituisce la somma degli elementi
const somma = (a, b) => a + b;

// Concatena, riceve un array di stringhe e le concatena
const concatena = (strArr) => strArr.reduce((totale, el) => totale + el);

// Cerca, riceve una stringa e dice se sono presenti caratteri non dell'alfabeto
const cerca = (str) => (/[^a-z|A-Z]/.test(str) ? "si" : "no");

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
```

#### Screenshot funzionamento:

![screenshot](./img/Screenshot%20testing.png)

#### Sitografia:

- [metodi degli array (per il metodo reduce)](https://www.w3schools.com/jsref/jsref_array[].asp)
- [metodi delle RegExp (per il metodo test)](https://www.w3schools.com/js/js_regexp.asp)

---

#### 27 Novembre 2025

### Creazione pagina di login

Ho creato la pagina di login e ho raffinato la grafica e anche riorganizzato la struttura dei file, in particolre dei file css.

Parte del codice html dell'index:

```html
[...]

<body>
  <!-- Navbar -->
  <nav>
    <ul>
      <li><a href="index.html" class="active">Home</a></li>
      <li><a href="shop.html">Shop</a></li>
      <li><a href="sales.html">Sales</a></li>
      <li><a href="chat.html">Chat</a></li>
      <li style="float: right"><a href="login.html">Login</a></li>
    </ul>
  </nav>

  <main>
    <!-- Logo -->
    <section id="logo" class="covering-section center-x center-y">
      <img
        width="90%"
        src="../img/EKHOIKOS!.svg"
        style="margin: 5vh; max-width: 1900px"
      />
      <a href="./shop.html">
        <button class="big-button rounded-corners">Shop Now!</button>
      </a>
      <p style="text-align: center; color: var(--info);">
        scopri cos'è Ekhoikos<br />|<br />|<br />v
      </p>
    </section>
  </main>
</body>

[...]
```

### Creazione pagina dello shop

Ho creato la pagina dello shop con le card per i prodotti, una lista di filtri e una sezione per mettere in seguito la mappa.

Parte del codice html del login:

```html
[...]

<form action="link.xyz" class="padding rounded-corners">
  <h1>Registrati</h1>
  <div class="form-fields">
    <label for="name">Nome:</label>
    <input type="name" id="name" name="name" />

    <label for="surname">Cognome:</label>
    <input type="surname" id="surname" name="surname" />

    <label for="username">Username:</label>
    <input type="text" id="username" name="username" />

    <label for="password">Password:</label>
    <input type="password" id="password" name="password" />

    <label for="passwordConfirm">Conferma password:</label>
    <input type="password" id="passwordConfirm" name="passwordConfirm" />
  </div>
  <input type="submit" id="form_submit" name="Login" />
</form>

[...]
```

---

#### 5 Dicembre 2025

### Modellazione database

Ho modellato il DB del sito web su carta e l'ho consegnato.

---

#### 19/12/2025

### Creazione del database

```sql
CREATE TABLE Users (
    User_ID int PRIMARY KEY AUTO_INCREMENT,
    Name varchar(64) NOT NULL,
    Surname varchar(64) NOT NULL,
    Username varchar(15) NOT NULL,
    Psw varchar(64) NOT NULL
);
CREATE TABLE Products (
    Creator_ID int,
    Name varchar(64) NOT NULL,
	  Description varchar(2048) NOT NULL,
    FOREIGN KEY (Creator_ID) REFERENCES Users(User_ID)
);
```

### Inserimento dei dati di prova

```sql
INSERT INTO users (Name, Surname, Username, Psw)
VALUES ("Mario", "Rossi", "Mrss_81", "passwordDifficilissima99"),
	("Alessia", "Verdi", "AVrd", "passwordDifficilissimissima101"),
    ("Baryon", "Moss", "Bjoiash", "ciao:)")
;

INSERT INTO products (Name, Description, Creator_ID) VALUES ("Foca Peluche", "Una carinissima e morbidissima foca peluche fatta interamente a mano per addormentarsi all'istante!", 1), ("Cornice A5 in larice decorata", "Cornice per immagini formato A5 in larice decorata con conchiglie marine.", 1), ("Sassi", "Ho raccolto dei sassi colorati. Vuoi comprarli? Sono a tua disposione.", 2);
```

### Query esempio

```sql
SELECT * FROM products WHERE Creator_ID = 1;
```
