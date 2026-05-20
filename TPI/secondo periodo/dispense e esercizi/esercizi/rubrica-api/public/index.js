// Modifica il comportament del tasto submit del form per non ricaricare la pagina
const form = document.getElementById("form-contatto");
form.addEventListener('submit', function(event) {
  event.preventDefault();
  aggiungiContatto();
})

const API_URL = `http://localhost:3000/api`;

let idInModifica = null;

// Scrivere nel log - mostrerà le chiamate all`API
function scriviLog(metodo, url, stato) {
  const log = document.getElementById(`api-log-entries`);
  const classe = `log-${metodo.toLowerCase()}`;
  const ora = new Date().toLocaleTimeString();
  
  // Elimina la scritta "latest" dall'ultima entry
  const latestText = document.getElementById("latestText");
  if(latestText){
    latestText.remove();
  }

  log.innerHTML = `<div class="log-entry">
    <span class="${classe}">[${metodo}]</span>
    ${url}
    -> <strong>${stato}</strong> <span style="color:#7f8c8d"> (${ora})  </span>
    <span id="latestText" style="color: green;">(LATEST)</span>
  </div>` + log.innerHTML;
}

// Mostra i messaggi di notifica temporanei
function mostraMessaggio(testo, tipo) {
  const div = document.getElementById(`messaggio`);
  div.textContent = testo;
  div.className = `messaggio messaggio-${tipo}`;
  div.style.display = `block`;

  setTimeout(() => {
    div.style.display = `none`;
  }, 5000);
}

async function caricaContatti() {
  try {
    const risposta = await fetch(`${API_URL}/contatti`);

    const dati = await risposta.json();

    scriviLog(`GET`, `/api/contatti`, risposta.status);
    if (dati.successo) {
      mostraListaContatti(dati.dati);
    }
  } catch (errore) {
    console.error(`Errore nel caricamento:`, errore);
    mostraMessaggio(`Errore di connessione al server!`, `errore`);
  }
}

function mostraListaContatti(dati) {
  creaTabella(dati);
}

function creaTabella(dati) {
  const container = document.getElementById("container-tabella");
  container.innerHTML = "";

  // Controlla che i dati (la rubrica) non siano vuoti
  if (!Array.isArray(dati) || dati.length === 0) {
    container.textContent = "Nessun contatto presente.";
    return;
  }

  // Crea l'elemento tabella
  const table = document.createElement("table");

  // Crea l'intestazione e la riga di intestazione
  const thead = document.createElement("thead");
  const headerRow = document.createElement("tr");

  // estrae le chiavi dal dict 'dati' per i nomi delle colonne
  const headers = Object.keys(dati[0]);
  // crea una colonna per ogni chiave del dict trovata
  headers.forEach(text => {
    const th = document.createElement("th");
    th.textContent = text;
    headerRow.appendChild(th);
  });

  thead.appendChild(headerRow);
  table.appendChild(thead);

  // Crea le righe del corpo della tabella
  const tbody = document.createElement("tbody");
  dati.forEach(item => {
    const row = document.createElement("tr");
    Object.values(item).forEach(value => {
      const cell = document.createElement("td");
      cell.textContent = value;
      row.appendChild(cell);
    });

    // Aggiunge una cella per la modifica del contatto con il bottone apposito
    const btnModifica = document.createElement("button");
    btnModifica.type = "button";
    btnModifica.onclick = () => preparaModifica(item.id, item.nome, item.cognome, item.telefono, item.email);
    btnModifica.textContent = "✏️";

    const btnElimina = document.createElement("button");
    btnElimina.type = "button";
    btnElimina.onclick = () => eliminaContatto(item.id, item.nome+" "+item.cognome);
    btnElimina.textContent = "❌";

    const cellModifica = document.createElement("td");
    cellModifica.appendChild(btnModifica);
    row.appendChild(cellModifica);

    const cellElimina = document.createElement("td");
    cellElimina.appendChild(btnElimina);
    row.appendChild(cellElimina);

    // Aggiunge la riga alla tabella
    tbody.appendChild(row);
  });
  table.appendChild(tbody);

  // Append al container della tabella
  document.getElementById("container-tabella").appendChild(table)
}

function pulisciForm() {
  document.getElementById(`input-nome`).value = ``;
  document.getElementById(`input-cognome`).value = ``;
  document.getElementById(`input-telefono`).value = ``;
  document.getElementById(`input-email`).value = ``;
}

async function aggiungiContatto() {
  // Legge i valori dei campi del form tramite il loro id
  const nome = document.getElementById(`input-nome`).value.trim();
  const cognome = document.getElementById(`input-cognome`).value.trim();
  const telefono = document.getElementById(`input-telefono`).value.trim();
  const email = document.getElementById(`input-email`).value.trim();

  if (!nome || !cognome) {
    mostraMessaggio(`Nome e cognome sono obbligatori!`, `errore`);
    return;
  }

  if (idInModifica !== null) {
    // Scorciatoia per modifica
    await modificaContatto(idInModifica, { nome, cognome, telefono, email});
    return;
  }

  try {
    const risposta = await fetch(`${API_URL}/contatti`, {
      method: `POST`,
      headers: { "Content-Type": "application/json"},
      body: JSON.stringify({ nome, cognome, telefono, email})
    });

    // Aspetta di capire se il server ha accettato il pacchetto
    const dati = await risposta.json();
    scriviLog(`POST`, `/api/contatti`, risposta.status);

    if (dati.successo) {
      mostraMessaggio(`Contatto "${nome} ${cognome}" creato!`, `successo`);
      pulisciForm();
      caricaContatti(); // Ricarica la lista
    } else {
      mostraMessaggio(dati.errore, `errore`);
    }
  } catch (errore) {
    console.error(`Errore nella creazione:`, errore);
    mostraMessaggio(`Errore di connessione al server!`, `errore`);
  }
}

async function modificaContatto(id, datiAggiornati) {
  try {
    const risposta = await fetch(`${API_URL}/contatti/${id}`, {
      method: `PUT`,
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify(datiAggiornati)
    });

    const dati = await risposta.json();
    scriviLog(`PUT`, `/api/contatti/${id}`, risposta.status);

    if (dati.successo) {
      mostraMessaggio(`Contatto aggiornato!`, `successo`);
      idInModifica = null;
      document.getElementById(`btn-submit`).value = `Salva contatto`;
      pulisciForm();
      caricaContatti();
    } else {
      mostraMessaggio(dati.errore, `errore`);
    }
  } catch (errore) {
    console.error(`Errore nella modifica`, errore);
    mostraMessaggio(`Errore di connessione al server`, `errore`);
  }
}

function preparaModifica(id, nome, cognome, telefono, email) {
  document.getElementById(`input-nome`).value = nome;
  document.getElementById(`input-cognome`).value = cognome;
  document.getElementById(`input-telefono`).value = telefono;
  document.getElementById(`input-email`).value = email;
  idInModifica = id;
  document.getElementById(`btn-submit`).value = `Aggiorna Contatto`;
  window.scrollTo({ top: 0, behavior: `smooth`}); // Fa tornare la pagina su
}

async function eliminaContatto(id, nomeCompleto) {
  if (!confirm(`Sei sicuro di voler eliminare ${nomeCompleto}?`)) {
    return; // Se l`user clicca "annulla" non succede niente
  }
  
  try {
    const risposta = await fetch(`${API_URL}/contatti/${id}`, {
      method: `DELETE`
    });
    const dati = await risposta.json();
    scriviLog(`DELETE`, `/api/contatti/${id}`, risposta.status);
    if (dati.successo) {
      mostraMessaggio(`"${nomeCompleto}" eliminato`, `successo`);
      caricaContatti();
    } else {
      mostraMessaggio(dati.errore, `errore`);
    }
  } catch (errore) {
    console.error(`Errore nell\`eliminazione:`, errore);
  }
}

caricaContatti();