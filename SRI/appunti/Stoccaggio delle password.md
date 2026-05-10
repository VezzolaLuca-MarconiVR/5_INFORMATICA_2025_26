Quando si vogliono salvare delle password in un database in sicurezza, si può procedere nel seguente modo:
- alla registrazione, il client (tramite connessione crittografata) invia nome utente e password al server
- il server esegue l'hash della password (+ un _salt_ casuale - per ovviare l'occorrenza di due password identiche per due user diversi) e la salva associata al nome utente