[Sito guida](https://wiki.ubuntu-it.org/Server/MySql)

## DataBase

### Installazione del DBMS (MySQL)
```bash
sudo apt update
sudoapt install mysql-server
```
// FORSE NON SERVE FARLO DA LOCALE - HO PROVATO SENZA
<!-- ### Configurazione del server
Aggiungere "bind-address = 127.0.0.1" (indicando l'IP della macchina sulla quale gira questo server) tramite:
```bash
sudo nano /etc/mysql/my.cnf
``` -->

### Creazione di un DataBase con una tabella con i seguenti campi: NomeUtente, Password, Nome, Cognome, eta, funzione

#### Si consideri come funzione: utente, amministratore, ...

### Popolazione del DataBase con 5 record a scelta

## PHP e HTML

### Installazione di PHP

### Creare una pagina web con campi di input username, password che fornisca come output Nome, Cognome, Eta, Funzione

### Generare una stringa SQL che, opportunamente inserita, faccia fornire, noto solo un username, la lista di username e password, cognome e funzione