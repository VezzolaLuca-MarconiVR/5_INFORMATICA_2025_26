# Server web multisito

## Setup host

Per poter risolvere dei nomi di server in indirizzi ip senza l'utilizzo di un server DNS serve modificare il file "hosts" della macchina (è preferibile usare una VM windows per non modificare il reindirizzamento della macchina fisica):

La posizione del file cambia da un sistema operativo all'altro, ma le tipiche posizioni sono le seguenti:

- Windows 10 – “C:\Windows\System32\drivers\etc\hosts”
- Linux – “/etc/hosts”
- Mac OS X – “/private/etc/hosts”

Esempio di file "hosts" modificato per risolvere due diversi siti dallo stesso IP:

```text
172.16.35.20 www.sito1.com //Descrizione
```

## Setup server:

### Creazione struttura

Ogni sito ha la sua intera struttura all'interno della propria cartella sul server in "/var/www", quindi serve creare una cartella root per ogni sito che si vuole aggiungere (in aggiunta a http, il dominio di base):

```shell
sudo mkdir -p /var/www/sito1/public_html
sudo mkdir -p /var/www/sito2/public_html
```

_"-p" sta per "parent", e permette di creare tutte le cartelle mancanti nella specifica del path._

Serve anche permettere l'accesso ad Apache ai file:

```shell
sudo chown -R $USER:$USER /var/www/sito1/public_html
sudo chown -R $USER:$USER /var/www/sito2/public_html
```

E successivamente creare un index.html in ognuna delle cartelle public_html utilizzando il comando nano.

### Creazione di un file di configurazione per ogni virtual host (sito)

Ora serve creare un file di configurazione distinto per ognuno dei siti creati:

```shell
sudo nano /etc/apache2/sites-available/sito1.conf
```

Esempio di file di configurazione dell'host virtuale:

```config
<VirtualHost *:80>
    ServerAdmin webmaster@sito1.com
    ServerName sito1.com
    ServerAlias www.sito1.com
    DocumentRoot /var/www/sito1/public_html
    ErrorLog ${APACHE_LOG_DIR}/sito1_error.log
    CustomLog ${APACHE_LOG_DIR}/sito1_access.log combined
</VirtualHost>
```

### Abilitazione dei siti appena creati

```shell
sudo a2ensite sito1.conf
sudo a2ensite sito2.conf
sudo systemctl reload apache2
```

Controlla per sicurezza se la sintassi è corretta:

```shell
sudo apache2ctl configtest
```

Una volta fatto ciò è possibile visitare il sito dalla VM Windows digitando il nome scritto nel file "host".

Il server riceverà un messaggio con all'interno il nome del virtualHost richiesto e lo comparerà con il contenuto dei file di configurazione per il reindirizzamento al dominio (alla root di carttelle) corretto.

Analisi del messaggio HTTP inviato al server Apache con nome dell'host (server):
![Analisi del messaggio HTTP inviato al server Apache](img/analisiGetConHost.png)

Possiamo notare come nella GET il primo parametro sia "Host: www.sito1.com" - qui è dove viene comunicato il nome dell'host (in questo caso virtualHost).
