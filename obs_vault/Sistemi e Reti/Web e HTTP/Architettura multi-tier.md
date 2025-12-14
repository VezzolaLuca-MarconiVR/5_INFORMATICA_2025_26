Una completa architettura di un'applicazione Web si configura, in genere, su tre livelli (architettura _three tier_):
1. interfaccia utente;
2. logica di funzionamento;
3. accesso ai dati.

Per **architettura multi-tier** si intende il modo in cui è suddiviso e organizzato il software che costituisce un'intera applicazione. Ogni livello svolge un particolare compito, i livelli comunicano tra loro e sono logicamente separati.
Una completa architettura di un'applicazione Web prevede che:
- il client (browser) chieda una pagina al server;
- il server Web chieda i dati a un DBMS server tramite del codice **SQL** embedded;
- il DBMS server esegua l'SQL e fornisca i dati al server Web;
- il server generi il codice HTML e lo invii al client;
- il client lo visualizzi sul dispositivo dell'utente.

### ZEND e STRUTS

Il **Model-View-Controller (MVC)** è un pattern di progettazione che separa i contenuti dalla presentazione.

Due esempi di MVC, comunemente usati nelle applicazioni Web, sono:
- **ZEND framework**, il quale offre servizi avanzati ed è costituito da un insieme di librerie open source scritte in PHP7 orientate ad oggetti. Le applicazioni sono guidate dagli eventi che ne controllano il flusso.
- **Apache STRUTS**, sviluppato da _Apache Software Foundation_, è basato su servlet Java (dei piccoli programmi eseguiti lato server - in opposizione agli applet, eseguiti lato client). Offre un modello basato su Eventi/Azioni in cui a ogni richiesta è associata l'azione da eseguire all'interno di una mappa XML precostruita.