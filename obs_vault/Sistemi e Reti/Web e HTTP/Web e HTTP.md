[HTML](HTML.md) è la "lingua" principale di internet e HTTP è il protocollo utilizzato per inviare file in quel formato.

# Il livello applicazione

HTTP, assieme a protocolli come DNS, FTP e SMTP si collocano al livello Applicazione del [Modello TCP](modelloTCP) e nei tre livelli superiori (Sessione, Presentazione e Applicazione) del [Modello ISO/OSI](Modello%20ISO-OSI.md).

# Funzionamento di un server Web

Un "Server Web" è l'applicazione software in esecuzione su un server che fornisce dei contenuti Web richiesti. Tale applicazione prende il nome di "demone" HTTP, o HTTPd (_HTTP Daemon_).
Il "demone" è costantemente in attesa di una richiesta da un client qualsiasi, e quando la richiesta arriva, cerca di soddisfarla andando ad individuare il file cercato.

Nei sistemi UNIX/LINUX il _daemon_ può, attraverso una _fork_, clonare se stesso, generando un figlio che si occuperà della richiesta per permettere al padre di tornare subito in ascolto.

## Architettura client-server

Un'applicazione di rete è solitamente basata su un'[architettura client-server](architetturaClientServer): il client richiede una risorsa al server, il quale risponde, tipicamente, con un file HTML che il browser del client interpreta e visualizza. Il percorso per individuare una risorsa in internet è un URL.

Quando viene richiesto un file, a meno di eventuali errori, si possono verificare due casi:
1. Il file HTML richiesto è già presente nella memoria di massa del server: il server lo recupera e lo invia al client, il quale lo visualizza a schermo. Il file HTML rappresenta una **pagina web statica**;
2. Il file HTML richiesto è generato dall'esecuzione di uno script eseguito dal server. Lo script genera un codice HTML che viene inviato al client. In questo caso si parla di **pagina web dinamica** (l'url della richiesta in questo caso è quello dello script - per esempio _"http://www.time.it/now.php"_).

***[APPROFONDIMENTO: Architettura multi-tier](Architettura%20multi-tier.md)***
***[APPROFONDIMENTO: AJAX](AJAX.md)***


# Il protocollo HTTP

HTTP (_Hyper Text Transfer Protocol_), insieme a HTTPS - la sua versione sicura -, è il protocollo che costituisce il fondamento della comunicazione del Web.
E' un protocollo che fa parte del livello applicazione e permette la collaborazione tra sistemi distribuiti in un modello client-server.
Si tratta di instaurare una sessione di comunicazione che permetta al client di richiedere risorse al server. Una sessione si stabilisce con una richiesta TCP alla porta 80 (o 443 se il protocollo è HTTPS). I messaggi sono costituiti da stringhe strutturate secondo una precisa sintassi.

## URI e URL

Un URI (_Uniform Resource Identifier_) è una stringa che identifica univocamente una risorsa in un sistema.
Un URL (_Uniform Resource Locator_) è un URI che identifica univocamente una risorsa sul Web (l'"indirizzo Web").

La struttura di un URL è la seguente (< > è obbligatorio, mentre [ ] è opzionale):
```
protocollo://nomeHost[:porta]</percorso>[?querystring][#fragmentIdentifier]
```

Può anche essere specificato un username e una password (per l'HTTP e l'HTTPS) - anche se altamente sconsigliato per la sicurezza - in questo modo:
```
protocollo://username:password@nomeHost
```


## La richiesta del client

L'obbiettivo di una richiesta HTTP è accedere a una risorsa identificata con un URL.
Un messaggio HTTP è costituito da una stringa ASCII costruita con la seguente sintassi:
```
| metodo HTTP | sp | URI | sp | versione HTTP | CR | LF |
| nome del campo | : | valore | CR | LF |
...
| nome del campo | : | valore | CR | LF |
| CR | LF |
| body |
```

Le righe terminano con i caratteri ASCII _CR (Carriage Return)_ e _LF (Line Feed)_, che spostano il cursore all'inizio della linea e poi in giù di una linea (corrispondono ad andare a capo). Gli elementi sono separati da caratteri di spazio (_sp_). Prima del body c'é una riga vuota (_CR_, _LF_).

Il metodo utilizzato specifica l'azione da far intraprendere al server. I metodi principali sono:

| Metodo  | Azione svolta dal Client                                                                                                 |
| ------- | ------------------------------------------------------------------------------------------------------------------------ |
| GET     | Richiede una risorsa ospitata sul server                                                                                 |
| POST    | Invia dati al server per creare o processare una risorsa                                                                 |
| HEAD    | Richiede al server di inviare solamente le informazioni riassuntive presenti nell'intestazione del messaggio di risposta |
| PUT     | Invia una rappresentazione completa di una risorsa al server per crearla o sostituirla                                   |
| DELETE  | Richiede al server di eliminare la risorsa identificata dall’URI                                                         |
| OPTIONS | Richiede al server di indicare i metodi HTTP e le opzioni di comunicazione supportate per la risorsa                     |

## La risposta del server

Anche il messaggio di risposta HTTP che il server invia al client consiste in una stringa ASCII:
```
| versione HTTP | sp | codice di stato | sp | descrizione | CR | LF |
| nome del campo | : | valore | CR | LF |
...
| nome del campo | : | valore | CR | LF |
| CR | LF |
| body |
```

Il **codice di stato** è un numero di tre cifre (seguito dalla sua descrizione) che il server invia al client per comunicare che cosa è accaduto durante l'elaborazione della richiesta, ed è così classificabile:
- da 200 a 299 ==> Successo;
- da 300 a 399 ==> Ridirezione;
- da 400 a 499 ==> Errore del client;
- da 500 a 599 ==> Errore del server.

Se la richiesta è andata a buon fine (codice 200), il body contiene il codice HTML della pagina richiesta o altri dati richiesti.

## Il passaggio di parametri

La comunicazione dei parametri avviene attraverso una stringa, e questa stringa è passata in modo diverso in base al metodo utilizzato: [[#Il metodo GET|GET]] o [[#Il metodo POST|POST]].

### Il metodo GET

Usando il metodo GET l'invio dei dati, in formato ASCII, avviene aggiungendo all'URL i parametri dopo il carattere "?", nel formato "campo=valore", e separati da "&":
```
http://server/percorso/programma?campo1=valore1&campo2=valore2
```

I dati possono essere digitati nella barra di ricerca oppure digitati in automatico all'invio di un form (il body non viene valorizzato).

Usando il comando GET, quindi, i parametri passati nell'URL sono visibili nella barra degli indirizzi del browser. Il server recupera i valori pervenuti leggendo la _QUERY_STRING_. La lunghezza massima della stringa è di 2048 caratteri.
#### Nota bene:
Nella query string i caratteri "+" rappresentano gli spazi e ogni "%" precede due caratteri esadecimali che devono essere poi interpretati come un unico carattere.

### Il metodo POST

A differenza del metodo GET, la stringa di informazioni viene passata nel body della richiesta. Non ci sono limiti di lunghezza per la stringa, e nei dati sono perfino ammessi valori binari.

# Considerazioni finali

- **HTTP non ha memoria** (è _stateless_, privo di uno stato): ogni richiesta HTTP è trattata dal server come unica e indipendente dalle altre.
- **HTTP è asimmetrico** (_pull-based_): è sempre e solo il client che chiama il server. Non esiste la possibilità che accada il contrario.
- **HTTP è nato per la trasmissione di pagine Web**, tuttavia con il tempo sono nati nuovi linguaggi e procedure di sviluppo software per inviare anche altre tipologie di dati.
- **HTTP non è sicuro**. Le informazioni passano in chiaro e possono essere facilmente intercettate e lette. Le informazioni riservate devono essere crittografate., e il protocollo HTTPS (***Secure HTTP***) è stato creato apposta per fare ciò.

***[APPROFONDIMENTO: Considerazioni sul protocollo HTTP](considerazioni%20sul%20protocollo%20HTTP.md)***
***[APPROFONDIMENTO: API Restful](API%20Restful.md)***
