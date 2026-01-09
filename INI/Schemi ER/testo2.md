

## **Testo dell’esercizio **

**Traccia:**

Una base spaziale gestisce il personale, le navicelle e le missioni spaziali. Si richiede di progettare un database che permetta di memorizzare le seguenti informazioni:

1. **Personale:**

   * Ogni persona ha un **ID univoco**, nome, cognome e ruolo (Astronauta, Ingegnere, Medico).
   * Gli **Astronauti** hanno un livello di esperienza e specializzazione;
   * Gli **Ingegneri** hanno un reparto di competenza;
   * I **Medici** hanno un elenco di specializzazioni mediche.

2. **Navicelle spaziali:**

   * Ogni navicella ha un **ID univoco**, nome e tipo (Cargo, Esplorativa).
   * Alcune navicelle hanno un modulo aggiuntivo (es. laboratorio o modulo di osservazione).

3. **Missioni spaziali:**

   * Ogni missione ha un **ID univoco**, nome, data di partenza e durata prevista.
   * Una missione può coinvolgere **più astronauti** e **una sola navicella**, ma una navicella può partecipare a più missioni.
   * Gli astronauti partecipano a missioni in un certo ruolo (es. comandante, pilota, scienziato).

4. **Associazioni aggiuntive:**

   * Ogni astronauta può essere assegnato a un solo laboratorio alla volta.
   * Ogni ingegnere supervisiona più moduli, ma ogni modulo ha un solo ingegnere responsabile .

**Richieste:**

1. Disegnare il **diagramma ER** completo con:

   * gerarchie per il personale,
   * entità deboli per i moduli delle navicelle,
   * associazioni uno-a-uno, uno-a-molti e molti-a-molti.

2. Trasformare il modello ER in uno **schema logico relazionale** indicando chiaramente chiavi primarie, chiavi esterne e eventuali attributi delle relazioni.

---



