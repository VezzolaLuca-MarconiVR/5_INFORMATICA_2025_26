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

### Creazione delle tabelle Utenti e Products

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

---

#### 23/01/2026

## Primi passi con PHP: inizializzazione di un DB e comandi di base in PHP

Cartella contenente i file del DB creato con xampp lite: `xampp-lite/apps/mysql/data/nomeDatabase`

### Creazione del database e della tabella utenti

```sql
create database Ekhoikos;

create table Users(
  user_code int AUTO_INCREMENT PRIMARY KEY,
  name varchar(50) not null,
  surname varchar(50) not null,
  email varchar(254) not null
);
```

### Inserimento dei dati di prova

```sql
insert into users(name, surname, email) VALUES
(
  "Mario", "Rosi", "mross@gmail.com"
),
(
  "Anna", "Verdi", "averd@gmail.com"
),
(
  "Maria", "Azzurri", "mazz@gmail.com"
);
```

### File PHP per una scmplice INSERT

[Source...](https://www.w3schools.com/php/php_mysql_insert.asp)

I file php devono essere inseriti dentro la cartella `www/myDB`

```php
  <?php
  // Dati fondamentali per la connessione al server DB
  $servername = "localhost"; // localhost per usare un server DB locale
  $username = "root"; // root because this is the "master user"
  $password = ""; // for now, no password is needed
  $dbname = "myDB";

  // Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
//Check connection
if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->eror;
}

$conn->close();

  ?>
```

### Passare i dati da una pagina HTML ad uno script PHP

```html
<!DOCTYPE html>
<html>
  <head>
    <title>Insert user</title>
  </head>
  <body>
    <!-- 'action' should contain the name of the php file that handles this form -->
    <form action="fileName.php" method="post">
      <label for="uname">Name:</label>
      <input type="text" id="uname" name="uname" />

      <label for="usurname">Surname:</label>
      <input type="text" id="usurname" name="usurname" />

      <label for="uemail">Email:</label>
      <input type="text" id="uemail" name="uemail" />

      <input type="submit" value="Insert User" />
    </form>
  </body>
</html>
```

---

#### 30/01/2026

## Esercitazione in laboratorio: creazione DB, popolamento e costruzione di query

```sql
create database Negozio;

create table categorie(
  id_categoria int AUTO_INCREMENT PRIMARY KEY,
  nome varchar(128) NOT null
);
CREATE table prodotti(
  id_prodotto int AUTO_INCREMENT PRIMARY KEY,
  nome varchar(128) NOT NULL,
  fornitore varchar(128) not null,
  id_categorie int,
  FOREIGN KEY (id_categorie) REFERENCES categorie(id_categoria),
  prezzo float not null
);
create table clienti(
  id_cliente int AUTO_INCREMENT PRIMARY KEY,
  nome varchar(128) not null,
  indirizzo varchar(256) not null,
  citta varchar(256) not null,
  nazione varchar(32) not null
);
create table ordini(
  id_ordine int AUTO_INCREMENT PRIMARY KEY,
  id_cliente int NOT NULL,
  FOREIGN KEY (id_cliente) REFERENCES clienti(id_cliente),
  data_ordine date not null
);
create table dettagli_ordini(
  id_ordine int,
  id_prodotto int,
  FOREIGN KEY (id_ordine) REFERENCES ordini(id_ordine),
  FOREIGN KEY (id_prodotto) REFERENCES prodotti(id_prodotto),
  quantità int not null,
  PRIMARY KEY (id_ordine, id_prodotto)
);
```

---

#### 6/02/2026

## Creazione file HTML e PHP di un form

Form di input e php

Prendere le pagine registrazione.html e registrazione.php, utilizzare il db negozio implementato e popolato la scorsa lezione, o uno simile, modificare tenendo conto di:

- Handling
- Validation
- Required
- Form url e-mail

Creare il file connessione.php, il file funzioni.php contenente la funzione test_input
Modificare il file registrazione.html e registrazione.php utilizzando prepared statements.
Consegnare il diario di bordo aggiornato e la cartella sito_cognome contenuta nella cartella www

Link utili:

- https://www.w3schools.com/html/html_form_input_types.asp
- https://www.w3schools.com/php/php_forms.asp
- https://www.w3schools.com/php/php_mysql_prepared_statements.asp

---

#### 1/03/2026

## Creazione di un sistema di Handling, Validation, Requirement, e Input Validation

Sistema di gestione form con validazione e connessione al database (con XAMPP).

## Componenti Principali

- `connessione.php` - Gestisce la connessione al database
```php
<?php
  // Inizializzazione delle variabili descrittive della connessione con il DB
  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "negozio";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

  $sql = "INSERT INTO Clienti (nome, indirizzo, citta, nazione)
  VALUES ('$unameAndSurname', '$uaddress', '$ucity', '$unation')";

  if ($conn->query($sql) === TRUE) {
    echo "<span class='success'>New client added successfully!</span>";
  } else {
  echo "Error: " . $sql . "<br>" . $conn->eror;
  }

  $conn->close();
?>
```
- `functions.php` - Contiene la funzione per correggere l'input in un formato ideale:
```php
<?php
function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}
?>
```
## Caratteristiche di Sicurezza

- Utilizza prepared statements per proteggere da SQL injection
- Valida tutti i dati ricevuti dal form

## Aggiunta di una lista di opzioni (select with options) all'HTML con JS

```js
const nationSelect = document.getElementById("nationSelect");

const nationsList = [
  "Afghanistan",
  "Albania",
  ...
  "Zimbabwe",
];

let node;
let textnode;

node = document.createElement("option");
textnode = document.createTextNode("-----");
node.appendChild(textnode);
node.setAttribute("value", ""); // "value" è nullo per l'opzione vuota
nationSelect.appendChild(node);

// Aggiunge un'opzione per ogni nazione nella lista con attributo "value" identico al nome dell'opzione
nationsList.forEach((el) => {
  node = document.createElement("option");

  textnode = document.createTextNode(el);
  node.appendChild(textnode);

  node.setAttribute("value", el);

  nationSelect.appendChild(node);
});

```

---

#### 11/03/2026

## SQL Select via PHP

Esercizi su select via script PHP server-side (con XAMPP).

## Select create

- `selectAll.php`
  ```php
  <?php
  // Reference: https://www.w3schools.com/php/php_mysql_select.asp

  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "negozio";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  $sql = "SELECT * from Clienti";
  // Execute the SQL query
  $result = $conn->query($sql);

  // Output a title
  echo "<h1>Query: SELECT * from Clienti</h1>";

  // Process the result set
  if ($result->num_rows > 0) {
    // Output data of each row
    while($row = $result->fetch_assoc()) {
      echo "<b>id:</b> " . $row["id_cliente"].
      "; <b>nome:</b> " . $row["nome"].
      "; <b>indirizzo:</b> " . $row["indirizzo"].
      "; <b>città:</b> " . $row["citta"].
      "; <b>nazione:</b> " . $row["nazione"].
      "<br>";
    }
  } else {
    echo "0 results";
  }

  $conn->close();
  ?>
  ```
  Risultato:
  ![Select All](./img/Screen%20Select%20All.png)

- `selectWhere.php`
  ```php
  <?php
  // Reference: https://www.w3schools.com/php/php_mysql_select.asp

  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "negozio";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  $sql = "SELECT id_cliente, nome from Clienti where nazione != 'Italia'";
  // Execute the SQL query
  $result = $conn->query($sql);

  // Output a title
  echo "<h1>Query: SELECT id_cliente, nome from Clienti where nazione != 'Italia'</h1>";

  // Process the result set
  if ($result->num_rows > 0) {
    // Output data of each row
    while($row = $result->fetch_assoc()) {
      echo "<b>id:</b> " . $row["id_cliente"].
      "; <b>nome:</b> " . $row["nome"].
      "<br>";
    }
  } else {
    echo "0 results";
  }

  $conn->close();
  ?>
  ```
  Risultato:
  ![Select Where](./img/Screen%20Select%20Where.png)

- `selectJoin.php`
  ```php
  <?php
  // Reference: https://www.w3schools.com/php/php_mysql_select.asp

  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "negozio";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  $sql = "SELECT P.id_prodotto, P.nome  from Prodotti AS P JOIN Categorie AS C on P.id_categorie = C.id_categoria WHERE C.nome = 'Libri e Riviste'";
  // Execute the SQL query
  $result = $conn->query($sql);

  // Output a title
  echo "<h1>Query: SELECT P.id_prodotto, P.nome  from Prodotti AS P JOIN Categorie AS C on P.id_categorie = C.id_categoria WHERE C.nome = 'Libri e Riviste'</h1>";

  // Process the result set
  if ($result->num_rows > 0) {
    // Output data of each row
    while($row = $result->fetch_assoc()) {
      echo "<b>id:</b> " . $row["id_prodotto"].
      "; <b>nome:</b> " . $row["nome"].
      "<br>";
    }
  } else {
    echo "0 results";
  }

  $conn->close();
  ?>
  ```
  Risultato:
  ![Select Join](./img/Screen%20Select%20Join.png)

---

#### 13/03/2026

## Creazione DB per progetto sito "Ekhoikos"

Creazione del database e delle tabelle con SQL.

## Creazione DB
```sql
CREATE DATABASE Ekhoikos;
```

## Creazione tabelle
```sql
CREATE TABLE Utenti(
  nomeUtente varchar(32) PRIMARY KEY,
  psw varchar(255) NOT NULL,
  nome varchar(64) NOT NULL,
  cognome varchar(64) NOT NULL,
  dNascita date NOT NULL,
  email varchar(320) NOT NULL UNIQUE
);

CREATE TABLE SpaziDiMemoria(
  idSpazio int PRIMARY KEY AUTO_INCREMENT,
  tier int(1)
);

CREATE TABLE Licenze(
  nome varchar(32) PRIMARY KEY,
  descrizione varchar(1024)
);

CREATE TABLE Venditori(
  nomeUtente varchar(32),
  digitaleOFisico ENUM('Digitale', 'Fisico'),
  FOREIGN KEY (nomeUtente) REFERENCES Utenti(nomeUtente),
  PRIMARY KEY (nomeUtente)
);

CREATE TABLE File(
  idFIle int AUTO_INCREMENT,
  idSpazio int,
  nome varchar(255),
  filePath varchar(260),
  dimensioneByte int NOT NULL,
  unicoYN boolean NOT NULL,
  FOREIGN KEY (idSpazio) REFERENCES SpaziDiMemoria(idSpazio),
  PRIMARY KEY (idFile, idSpazio)
);

CREATE TABLE Prodotti(
  idProd int AUTO_INCREMENT,
  nomeVenditore varchar(32),
  statoProd ENUM('Disponibile', 'Esaurito', 'Su ordinazione'),
  descrizione varchar(1024),
  nome varchar(32) NOT NULL,
  prezzo decimal(10, 2) NOT NULL,
  quantita int,
  acconto decimal(10, 2),
  FOREIGN KEY (nomeVenditore) REFERENCES Venditori(nomeUtente),
  PRIMARY KEY (idProd, nomeVenditore)
);

CREATE TABLE ProdottiVenduti(
  idProd int,
  nomeVenditore varchar(32),
  nomeCliente varchar(32),
  stelle int CHECK (stelle BETWEEN 1 AND 5),
  puntiEco int CHECK (puntiEco BETWEEN 1 AND 5),
  recensione varchar(512),
  FOREIGN KEY (idProd, nomeVenditore) REFERENCES Prodotti(idProd, nomeVenditore),
  FOREIGN KEY (nomeCliente) REFERENCES Utenti(nomeUtente)
);

CREATE TABLE Richieste(
  idRichiesta int AUTO_INCREMENT,
  nomeCliente varchar(32),
  idProd int,
  nomeVenditore varchar(32),
  statoRichiesta ENUM('In attesa', 'Accettata', 'Completata', 'Rifiutata'),
  specificazioni varchar(512),
  FOREIGN KEY (nomeCliente) REFERENCES Utenti(nomeUtente),
  FOREIGN KEY (idProd, nomeVenditore) REFERENCES Prodotti(idProd, nomeVenditore),
  PRIMARY KEY (idRichiesta, nomeCliente, idProd, nomeVenditore)
);

CREATE TABLE ProdottiFisici(
  idProd int,
  nomeVenditore varchar(32),
  pesoKg decimal(3,2),
  FOREIGN KEY (idProd, nomeVenditore) REFERENCES Prodotti(idProd, nomeVenditore),
  PRIMARY KEY (idProd, nomeVenditore)
);

CREATE TABLE ProdottiDigitali(
  idProd int,
  nomeVenditore varchar(32),
  FOREIGN KEY (idProd, nomeVenditore) REFERENCES Prodotti(idProd, nomeVenditore),
  PRIMARY KEY (idProd, nomeVenditore)
);

CREATE TABLE FileInProdottiDigitali(
  idFile int,
  idSpazio int,
  idProd int,
  nomeVenditore varchar(32),
  FOREIGN KEY (idFile, idSpazio) REFERENCES File(idFile, idSpazio),
  FOREIGN KEY (idProd, nomeVenditore) REFERENCES ProdottiDigitali(idProd, nomeVenditore),
  PRIMARY KEY (idFile, idSpazio, idProd, nomeVenditore)
);
```

## Popolamento tabelle
```sql
-- =============================================================
--  POPOLAMENTO DATABASE - Ekhoikos Marketplace
--  Piattaforma e-commerce per prodotti artigianali ed ecologici
-- =============================================================


-- -------------------------------------------------------------
-- 1. UTENTI  (5 venditori + 5 clienti)
-- -------------------------------------------------------------
INSERT INTO Utenti (nomeUtente, psw, nome, cognome, dNascita, email) VALUES
('giulia_verde',  '$2b$12$KH8eFqLmN3pQrStUvWxYOuGreenCeramicsHashedPassword00001', 'Giulia',    'Verdi',     '1990-03-15', 'giulia.verdi@ekhoikos.it'),
('marco_bosco',   '$2b$12$AbCdEfGhIjKlMnOpQrStWoodWorkerHashedPasswordItaly00002', 'Marco',     'Boschi',    '1985-07-22', 'marco.boschi@ekhoikos.it'),
('sofia_luna',    '$2b$12$ZyXwVuTsRqPoNmMacrameNaturalFibersHashedPassword00003',  'Sofia',     'Lunardi',   '1993-11-08', 'sofia.lunardi@ekhoikos.it'),
('pietro_sole',   '$2b$12$MnOpQrStUvNaturalSoapsOrganicIngredientsHashed000004',   'Pietro',    'Soleri',    '1978-05-30', 'pietro.soleri@ekhoikos.it'),
('elena_foglia',  '$2b$12$FgHiJkLmBotanicalArtDigitalPatternsHashedPassword00005', 'Elena',     'Fogliani',  '1995-09-12', 'elena.fogliani@ekhoikos.it'),
('luca_fiume',    '$2b$12$RsTuVwXyClienteBuyerLucaFiumaraHashedPassword000006',    'Luca',      'Fiumara',   '1988-02-14', 'luca.fiumara@ekhoikos.it'),
('anna_terra',    '$2b$12$PqRsTuVwClienteAnnaTerranovaHashedPassword0000007',      'Anna',      'Terranova', '1992-06-25', 'anna.terranova@ekhoikos.it'),
('chiara_vento',  '$2b$12$BcDeFgHiClienteChiaraVentosiHashedPassword000000008',    'Chiara',    'Ventosi',   '1997-01-03', 'chiara.ventosi@ekhoikos.it'),
('fabio_pietra',  '$2b$12$JkLmNoPqClienteFabioPietraniHashedPassword00000009',     'Fabio',     'Pietrani',  '1983-08-18', 'fabio.pietrani@ekhoikos.it'),
('riccardo_mare', '$2b$12$XyZ01234ClienteRiccardoMarelliHashedPassword000010',     'Riccardo',  'Marelli',   '1991-12-07', 'riccardo.marelli@ekhoikos.it');


-- -------------------------------------------------------------
-- 2. SPAZI DI MEMORIA  (tier 1 = base, 2 = standard, 3 = pro)
-- -------------------------------------------------------------
INSERT INTO SpaziDiMemoria (tier) VALUES
(1),   -- idSpazio = 1  (sofia_luna, piano base)
(2),   -- idSpazio = 2  (sofia_luna, piano standard)
(3);   -- idSpazio = 3  (elena_foglia, piano pro)


-- -------------------------------------------------------------
-- 3. LICENZE
-- -------------------------------------------------------------
INSERT INTO Licenze (nome, descrizione) VALUES
('CC BY 4.0',
 'Creative Commons Attribuzione 4.0 Internazionale. Consente uso, condivisione, adattamento e distribuzione, anche commerciale, a condizione di citare adeguatamente l autore originale.'),
('CC BY-NC 4.0',
 'Creative Commons Attribuzione-Non Commerciale 4.0. Permette uso e condivisione libera solo per scopi non commerciali, con obbligo di attribuzione all autore.'),
('CC BY-ND 4.0',
 'Creative Commons Attribuzione-Non opere derivate 4.0. Consente redistribuzione, anche commerciale, solo nella forma originale e senza modifiche, con attribuzione.'),
('Uso Personale',
 'Licenza esclusiva per uso strettamente personale e privato. Non e consentita la redistribuzione, la pubblicazione o l utilizzo commerciale del file acquistato.');


-- -------------------------------------------------------------
-- 4. VENDITORI
-- -------------------------------------------------------------
INSERT INTO Venditori (nomeUtente, digitaleOFisico) VALUES
('giulia_verde',  'Fisico'),
('marco_bosco',   'Fisico'),
('sofia_luna',    'Digitale'),
('pietro_sole',   'Fisico'),
('elena_foglia',  'Digitale');


-- -------------------------------------------------------------
-- 5. FILE  (allegati ai prodotti digitali)
-- -------------------------------------------------------------
INSERT INTO File (idSpazio, nome, filePath, dimensioneByte, unicoYN) VALUES
-- File di sofia_luna (spazio tier 2, idSpazio = 2)
(2, 'schema_macrame_base.pdf',       '/storage/tier2/sofia_luna/schema_macrame_base.pdf',       2457600, FALSE),  -- idFile = 1
(2, 'schema_macrame_avanzato.pdf',   '/storage/tier2/sofia_luna/schema_macrame_avanzato.pdf',   3145728, FALSE),  -- idFile = 2
(2, 'ricamo_mandala_schema.pdf',     '/storage/tier2/sofia_luna/ricamo_mandala_schema.pdf',     1572864, FALSE),  -- idFile = 3
-- File di elena_foglia (spazio tier 3, idSpazio = 3)
(3, 'stampa_botanica_felce.png',     '/storage/tier3/elena_foglia/stampa_botanica_felce.png',   8388608, TRUE),   -- idFile = 4
(3, 'stampa_botanica_iris.png',      '/storage/tier3/elena_foglia/stampa_botanica_iris.png',    7340032, TRUE),   -- idFile = 5
(3, 'pattern_tessuto_natura.svg',    '/storage/tier3/elena_foglia/pattern_tessuto_natura.svg',   524288, FALSE);  -- idFile = 6


-- -------------------------------------------------------------
-- 6. PRODOTTI
--    statoProd: 'Disponibile' | 'Esaurito' | 'Su ordinazione'
-- -------------------------------------------------------------
INSERT INTO Prodotti (idProd, nomeVenditore, statoProd, descrizione, nome, prezzo, quantita, acconto) VALUES

-- === Giulia Verde – Ceramica con argilla naturale ===
(1,  'giulia_verde', 'Disponibile',
 'Tazza in ceramica lavorata a mano con argilla naturale estratta localmente e smaltatura ecologica priva di piombo e cadmio. Ogni pezzo e unico, decorato con motivi botanici incisi a mano prima della cottura.',
 'Tazza Botanica in Ceramica',            28.00,  12, NULL),

(2,  'giulia_verde', 'Disponibile',
 'Set di 4 piattini in ceramica artigianale realizzati con argilla di recupero da scarti di lavorazione. Decorati con pigmenti naturali e ossidi minerali. Adatti per dolci, formaggi stagionati o come sottobicchieri.',
 'Set Piattini in Ceramica Naturale',     45.00,   6, NULL),

(3,  'giulia_verde', 'Su ordinazione',
 'Vaso in ceramica completamente personalizzabile: il cliente sceglie forma, dimensione e motivo decorativo. Realizzato con argilla locale e tecniche di cottura a bassa emissione di CO2. Tempi di consegna: 3-4 settimane.',
 'Vaso Ceramica Personalizzato',          65.00, NULL, 20.00),

-- === Marco Bosco – Legno di recupero ===
(4,  'marco_bosco',  'Disponibile',
 'Tagliere ricavato da un tronco di noce recuperato da potature locali. Trattato esclusivamente con olio di lino biologico, senza vernici o prodotti chimici. Le venature sono uniche su ogni pezzo.',
 'Tagliere in Legno di Noce Recuperato', 38.00,   8, NULL),

(5,  'marco_bosco',  'Disponibile',
 'Cornice per foto realizzata con rami e legni di recupero raccolti nel bosco vicino al laboratorio. Formato 15x20 cm. Finitura a cera d api biologica per esaltare il colore naturale del legno.',
 'Cornice Rustica in Legno di Recupero', 22.00,  15, NULL),

-- === Sofia Luna – Tessile naturale e macrame ===
(6,  'sofia_luna',   'Disponibile',
 'Appendiabiti da parete intrecciato a mano in macrame con cordino di cotone biologico non sbiancato. Completamente privo di coloranti sintetici. Dimensioni: circa 40x60 cm. Gancio in legno di pino recuperato.',
 'Appendiabiti Macrame Cotone Bio',       35.00,  10, NULL),

(7,  'sofia_luna',   'Disponibile',
 'Schema PDF scaricabile per realizzare un appendiabiti in macrame e un ricamo mandala. Istruzioni passo passo, lista materiali eco-compatibili, varianti cromatiche con tinture naturali. Adatto a principianti e intermedi.',
 'Schema Macrame & Ricamo Mandala',       12.00, NULL, NULL),

-- === Pietro Sole – Saponi e cosmetici naturali ===
(8,  'pietro_sole',  'Disponibile',
 'Sapone artigianale al carbone vegetale attivo e argilla verde. Ingredienti 100% naturali e biodegradabili, senza SLS, parabeni o profumi sintetici. Peso circa 100g. Confezionato in carta kraft riciclata.',
 'Sapone Artigianale Carbone & Argilla',  8.50,  30, NULL),

(9,  'pietro_sole',  'Disponibile',
 'Kit da 3 saponi artigianali profumati con oli essenziali biologici certificati: lavanda, tea tree e arancia dolce. Ingredienti naturali e cruelty-free, testati su pelli sensibili. Ottimo come idea regalo sostenibile.',
 'Kit Saponi Artigianali Oli Essenziali', 22.00,  18, NULL),

-- === Elena Foglia – Arte botanica digitale ===
(10, 'elena_foglia', 'Disponibile',
 'Stampa artistica botanica su carta cotone 300g riciclata al 50%, formato A4. Raffigura felci e iris selvatiche scansionate ad alta risoluzione. Ogni stampa e numerata e firmata a mano. Spedita in tubo riciclato.',
 'Stampa Artistica Botanica - Serie A',   40.00,   5, NULL),

(11, 'elena_foglia', 'Disponibile',
 'Pack di pattern digitali in formato SVG ad alta risoluzione ispirati alla natura: foglie, ramoscelli e fiori selvatici. Pronti per uso su tessuti, carta da parati, packaging eco e progetti grafici sostenibili.',
 'Pattern Digitali Botanici SVG',         18.00, NULL, NULL);


-- -------------------------------------------------------------
-- 7. PRODOTTI FISICI  (pesoKg per calcolo spedizione eco)
-- -------------------------------------------------------------
INSERT INTO ProdottiFisici (idProd, nomeVenditore, pesoKg) VALUES
(1,  'giulia_verde', 0.35),
(2,  'giulia_verde', 0.60),
(3,  'giulia_verde', 0.80),
(4,  'marco_bosco',  0.75),
(5,  'marco_bosco',  0.30),
(6,  'sofia_luna',   0.20),
(8,  'pietro_sole',  0.10),
(9,  'pietro_sole',  0.30),
(10, 'elena_foglia', 0.05);


-- -------------------------------------------------------------
-- 8. PRODOTTI DIGITALI
-- -------------------------------------------------------------
INSERT INTO ProdottiDigitali (idProd, nomeVenditore) VALUES
(7,  'sofia_luna'),
(11, 'elena_foglia');


-- -------------------------------------------------------------
-- 9. FILE IN PRODOTTI DIGITALI
--    Prodotto 7  (sofia_luna)  → file 1, 2, 3  (idSpazio = 2)
--    Prodotto 11 (elena_foglia) → file 6        (idSpazio = 3)
-- -------------------------------------------------------------
INSERT INTO FileInProdottiDigitali (idFile, idSpazio, idProd, nomeVenditore) VALUES
(1, 2,  7,  'sofia_luna'),   -- schema_macrame_base.pdf
(2, 2,  7,  'sofia_luna'),   -- schema_macrame_avanzato.pdf
(3, 2,  7,  'sofia_luna'),   -- ricamo_mandala_schema.pdf
(6, 3,  11, 'elena_foglia'); -- pattern_tessuto_natura.svg


-- -------------------------------------------------------------
-- 10. PRODOTTI VENDUTI
-- -------------------------------------------------------------
INSERT INTO ProdottiVenduti (idProd, nomeVenditore, nomeCliente) VALUES
(1,  'giulia_verde', 'luca_fiume'),
(1,  'giulia_verde', 'anna_terra'),
(4,  'marco_bosco',  'chiara_vento'),
(5,  'marco_bosco',  'riccardo_mare'),
(6,  'sofia_luna',   'fabio_pietra'),
(7,  'sofia_luna',   'anna_terra'),
(7,  'sofia_luna',   'riccardo_mare'),
(8,  'pietro_sole',  'luca_fiume'),
(9,  'pietro_sole',  'chiara_vento'),
(10, 'elena_foglia', 'riccardo_mare'),
(11, 'elena_foglia', 'fabio_pietra');


-- -------------------------------------------------------------
-- 11. RICHIESTE DI PERSONALIZZAZIONE
--     statoRichiesta: 'In attesa' | 'Accettata' | 'Completata' | 'Rifiutata'
-- -------------------------------------------------------------
INSERT INTO Richieste (nomeCliente, idProd, nomeVenditore, statoRichiesta, specificazioni) VALUES

('luca_fiume',    3, 'giulia_verde', 'Accettata',
 'Vaso di medie dimensioni (circa 25 cm di altezza) con motivi a foglie di ulivo incisi. Colori: terracotta naturale con sfumature verdi. Vorrei anche un foro di drenaggio sul fondo.'),

('anna_terra',    3, 'giulia_verde', 'In attesa',
 'Vaso piccolo per piante grasse, con foro di drenaggio. Decorazione geometrica minimal stile nordico. Preferisco toni neutri: beige sabbia e grigio ardesia.'),

('riccardo_mare', 3, 'giulia_verde', 'Completata',
 'Grande vaso da esterno resistente alle intemperie per pianta di limone (diam. 35 cm). Motivo con onde marine stilizzate. Colori: blu ceruleo e bianco calce.'),

('chiara_vento',  6, 'sofia_luna',   'In attesa',
 'Schema per un appendiabiti macrame in versione XL (circa 60x90 cm) con frange lunghe e almeno 8 ganci.'),

('fabio_pietra',  9, 'pietro_sole',  'Rifiutata',
 'Possibile sostituire i profumi standard con eucalipto, menta piperita e rosa mosqueta biologica? Confezionamento in scatola regalo in cartone riciclato con nastro in cotone invece del cellofan.');
```

### Nota:

All'inserimento dei dati, le password sono crittate dal PHP nella seguente maniera:
```php
$password = "user_secret_password";
$hash = password_hash($password, PASSWORD_DEFAULT);

// Save $hash to your database. 
// Use a VARCHAR(255) column to allow for future algorithm changes.
```

Verifica degli utenti:
```php
$user_input = $_POST['password']; // Password from login form
$stored_hash = "..."; // Hash retrieved from your database

if (password_verify($user_input, $stored_hash)) {
    echo "Password is valid!";
} else {
    echo "Invalid password.";
}
```

---

#### 27/03/2026

## Implementazione delle sessioni

Implementazione delle sessioni con variabili 'logged_in' booleano e 'username'.
Si prevede di aggiungere 'theme' per la preferenza tra tema chiaro e scuro.

---

#### 9/04/2026

## Correzzione Login e Logout

Sono stati corretti i file di Login e Logout (ATTENTO: connect.php sovrascriveva la variabile username, quidni l'ho cambiata).

## Implementazione del negozio

Lo 'Shop' ora mostra tutti i prodotti disponibili e una mappa del territorio al lato (qui sono a scopo illustrativo, non serve a nulla dato che non possiamo aggiungere dati fittizzi a maps).

### Implementazione delle immagini dei prodotti nel DB

Implementazione delle immagini dei prodotti nel DB mediante l'aggiunta del path dell'immagine alla tabella dei prodotti:
```sql
ALTER TABLE `prodotti` ADD `url` VARCHAR(255) NULL AFTER `acconto`;
```