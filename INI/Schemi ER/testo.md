

## 📘 Esercizio pausa didattica

**Progettazione di basi di dati**

### Quesito

Si richiede la progettazione di una **base di dati per la gestione di una Università**, al fine di organizzare le informazioni relative a persone, studenti, docenti, corsi, iscrizioni, tessere universitarie ed esami.

---

### Descrizione del sistema

Ogni **Persona** è identificata univocamente da una *Matricola* ed è caratterizzata da *Nome*, *Cognome* e *Data di nascita*.
Una persona può essere **Studente** oppure **Docente**.

Ogni **Studente** è caratterizzato anche dal *Corso di laurea* a cui è iscritto.
Ogni **Docente** è caratterizzato dal *Dipartimento* di appartenenza.

Ogni **Corso** è identificato da un *CodiceCorso* ed è caratterizzato da *Nome* e *Crediti formativi (CFU)*.
Un **Docente** può tenere più **Corsi**, mentre ogni **Corso** è tenuto da un solo **Docente**.

Uno **Studente** può iscriversi a più **Corsi**, e ogni **Corso** può avere più **Studenti iscritti**.

Ogni **Studente** possiede una sola **Tessera universitaria** e ogni **Tessera universitaria** appartiene a un solo **Studente**.

La Tessera universitaria è caratterizzata da *Numero tessera* e *Data di rilascio*.

Per ogni **Corso** possono essere organizzati più **Esami**.
Ogni **Esame** è identificato da un *Numero di appello* valido esclusivamente all’interno del Corso a cui è associato e non può esistere indipendentemente dal Corso stesso.
L’Esame è caratterizzato da *Data* e *Aula*.

---

### Richieste

Il candidato:

1. realizzi il **diagramma Entity-Relationship (ER)** della base di dati descritta;
2. evidenzi nel diagramma:

   * la **gerarchia di classi**;
   * le associazioni di tipo **uno a molti (1–N)**, **molti a molti (N–M)** e **uno a uno (1–1)**;
   * l’**entità debole** e la relativa **chiave**;
3. traduca il diagramma ER nel **modello logico relazionale**, specificando:

   * le **chiavi primarie**;
   * le **chiavi esterne**.

---




