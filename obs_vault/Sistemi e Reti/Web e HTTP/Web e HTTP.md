[HTML](HTML.md) è la "lingua" principale di internet e HTTP è il protocollo utilizzato per inviare file in quel formato.

# Il livello applicazione

HTTP, assieme a protocolli come DNS, FTP e SMTP si collocano al livello Applicazione del [Modello TCP](modelloTCP) e nei tre livelli superiori (Sessione, Presentazione e Applicazione) del [Modello ISO/OSI](modelloISO/OSI).

# Funzionamento di un server Web

Un "Server Web" è l'applicazione software in esecuzione su un server che fornisce dei contenuti Web richiesti. Tale applicazione prende il nome di "demone" HTTP, o HTTPd (_HTTP Daemon_).
Il "demone" è costantemente in attesa di una richiesta da un client qualsiasi, e quando la richiesta arriva, cerca di soddisfarla andando ad individuare il file cercato.

Nei sistemi UNIX/LINUX il _daemon_ può, attraverso una _fork_, clonare se stesso, generando un figlio che si occuperà della richiesta per permettere al padre di tornare subito in ascolto.

# Architettura client-server

Un'applicazione di rete è solitamente basata su un'[architettura client-server](architetturaClientServer): il client richiede una risorsa al server, il quale risponde, tipicamente, con un file HTML che il browser del client interpreta e visualizza. Il percorso per individuare una risorsa in internet è un URL.

Quando viene richiesto un file 