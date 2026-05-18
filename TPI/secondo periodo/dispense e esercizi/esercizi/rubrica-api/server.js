// Cerca le librerie in `node_modules/` e le carica
const express = require(`express`);
const cors = require(`cors`);

// Crea l`applicazione express
const app = express();

// I browser bloccano per sicurezza le chiamate tra siti o porte diverse.
// Questa istruzione permette richieste da altri domini.
app.use(cors());

// Permette al server di leggere dati in formato JSON nel corpo delle richieste, traducendoli in oggetti JavaScript.
app.use(express.json());

// Permette di inviare i file statici.
app.use(express.static(`public`));

// Per semplicità i dati saranno salvati in un array JS e non in un DB:
let prossimoId = 3;
let contatti = [
  {
    id: 1,
    nome: "Mario",
    cognome: "Rossi",
    telefono: "333-1234567",
    email: "mario.rossi@email.it"
  },
  {
    id: 2,
    nome: "Laura",
    cognome: "Bianchi",
    telefono: "340-9876543",
    email: "laura.bianchi@email.it"
  }
];


// Metodo: GET
// URL: http://localhost:3000/api/contatti
// Cosa fa: Restituisce la lista completa dei contatti
app.get(`/api/contatti`, (req, res) => {
  // `req` è la richiesta del client
  // `res` è la risposta del server
  res.json({
    successo: true,
    risultati: contatti.length,
    dati: contatti
  });
}); // La risposta è organizzata in JSON in diversi campi


// Metodo: GET
// URL: http://localhost:3000/api/contatti/1
// Cosa fa: Restituisce i dettagli di un contatto
app.get(`/api/contatti/:id`, (req, res) => {
  const id = parseInt(req.params.id);
  
  const indice = contatti.findIndex(c => c.id === id);

  if (indice === -1) {
    return res.status(404).json({
      successo: false,
      errore: `Contatto con ID ${id} non trovato`
    });
  }

  contatto = contatti[indice];

  return res.status(200).json({
    successo: true,
    dati: contatto
  });
});


// Metono: POST
// URL: http://localhost:3000/api/contatti
// Cosa fa: Aggiunge un nuovo contatto alla lista
app.post(`/api/contatti`, (req, res) => {
  // `req.body` contiene i dati inviati dal client nel corpo della richiesta
  const { nome, cognome, telefono, email} = req.body;
  
  // Controlla che i campi obbligatori ci siano
  if (!nome | !cognome) {
    return res.status(400).json({
      successo: false,
      errore: `Nome e cognome sono obbligatori`
    });
  }

  const nuovoContatto = {
    id: prossimoId,
    nome: nome,
    cognome: cognome,
    telefono: telefono || ``, // Se è vuoto, viene inserita una stringa vuota
    email: email || `` // Se è vuoto, viene inserita una stringa vuota
  };

  // Incremento dell`id per il prossimo contatto
  prossimoId++;

  // Aggiunta del nuovo contatto all`array
  contatti.push(nuovoContatto);

  // Risposta al client con codice 201 (Created)
  res.status(201).json({
    successo: true,
    messaggio: `Contatto creato con successo`,
    dati: nuovoContatto
  });
});


// Metodo: PUT
// URL: http://localhost:3000/api/contatti/1
// Cosa fa: Aggiorna i campi specificati del contatto
app.put(`/api/contatti/:id`, (req, res) => {
  // Esegue il parsing dell`id "catturato" dall`url della richiesta
  const id = parseInt(req.params.id);

  // `findIndex` restituisce la posizione nell`array dell`indice specificato (-1 se non trovato)
  const indice = contatti.findIndex(c => c.id === id);

  if (indice === -1) {
    return res.status(404).json({
      successo: false,
      errore: `Contatto con ID ${id} non trovato`
    });
  }

  // Aggiornamento dei soli campi che il client ha inviato
  const { nome, cognome, telefono, email} = req.body;
  if (nome) contatti[indice].nome = nome;
  if (cognome) contatti[indice].cognome = cognome;
  if (telefono) contatti[indice].telefono = telefono;
  if (email) contatti[indice].email = email;

  res.json({
    successo: true,
    messaggio: `Contatto aggiornato con successo`,
    dati: contatti[indice]
  });
});


// Metodo: DELETE
// URL: http://localhost:3000/api/contatti/1
// Cosa fa: Rimuove il contatto con l`ID specificato
app.delete(`/api/contatti/:id`, (req, res) => {
  const id = parseInt(req.params.id);

  const indice = contatti.findIndex(c => c.id === id);

  if (indice === -1) {
    return res.status(404).json({
      successo: false,
      errore: `Contatto con ID ${id} non trovato`
    });
  }

  // `splice` ritorna gli elementi tolti
  const eliminato = contatti.splice(indice, 1)[0];

  res.json({
    successo: true,
    messaggio: `Contatto eliminato`,
    dati: eliminato
  });
});


// Definiamo la porta di rete da utilizzare
const PORTA = 3000;

// Mette in ascolto il framework express.
// I messaggi di log verranno mostrati solo se non ci sono stati problemi durante l`avvio.
app.listen(PORTA, () => {
  console.log(`==============================================`);
  console.log(`  Server avviato!`);
  console.log(`  Apri: http://localhost:${PORTA}`);
  console.log(`==============================================`);
});

// Per testarlo: (dalla cartella del progetto) node server.js