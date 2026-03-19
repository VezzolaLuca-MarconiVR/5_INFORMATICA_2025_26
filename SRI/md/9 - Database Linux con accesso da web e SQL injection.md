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
(Si consideri come funzione: utente, amministratore)
```sql
CREATE DATABASE IdleDB;

CREATE TABLE Utenti(
    nomeUtente varchar(32) PRIMARY KEY,
    password varchar(32) NOT NULL,
    nome varchar(64) NOT NULL,
    cognome varchar(64) NOT NULL,
    eta int NOT NULL,
    funzione ENUM('utente', 'amministratore'),
);
```

### Popolazione del DataBase con 5 record a scelta
```sql
INSERT INTO Utenti(nomeUtente, password, nome, cognome, eta, funzione) VALUES
    ('paoloTack', 'Sistemi4Ever!!!', 'Paolo', 'Tacchella', 50, 'amministratore'),
    ('gioggiaM', 'SonoUnaDonna99', 'Gioggia', 'Mellonni', 49, 'amministratore'),
    ('tajuzAndo', '_ValeFinoAUnCertoPunto_', 'Andonio', 'Tajani', 72, 'utente'),
    ('crostetto', 'Poveri77Frustrati', 'Guido', 'Crosetto', 62, 'utente'),
    ('andrePizzi', 'METEOMETEOMETEO', 'Andrea', 'Pizzeghella', 49, 'utente');
```

## PHP e HTML
Pagina HTML racchiusa in uno script PHP:
```html
<!DOCTIPE html>
<html>
    <head>
        <title>Per piacere non fate una SQL Injection qui</title>
    </head>
    <body>
        <form action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>" method='POST'>
            <label for='uuser'>Username:</label>
            <input type='text' id='uuser' name='uuser'>

            <label for='upsw'>Password:</label>
            <input type='password' id='upsw' name='upsw'>

            <input type='submit' value='Login'/>
        </form>
        <?php
            // Inizializzazione delle variabili descrittive della connessione con il DB
            $servername = "localhost";
            $username = "root";
            $password = "";
            $dbname = "IdleDB";

            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) {
                die("Connection to DB failed: " . $conn->connect_error);
            }

            
        ?>
    </body>
</html>
```

### Installazione di PHP

### Creare una pagina web con campi di input username, password che fornisca come output Nome, Cognome, Eta, Funzione

### Generare una stringa SQL che, opportunamente inserita, faccia fornire, noto solo un username, la lista di username e password, cognome e funzione