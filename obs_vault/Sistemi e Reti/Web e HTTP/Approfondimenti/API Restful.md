Molte applicazioni web mettono a disposizione degli sviluppatori dei metodi per raggiungere le loro risorse nel modo più semplice possibile.
Il sistema di interfacciamento è presentato su pochi, ma significativi vincoli, che rendono semplice l'accesso ai servizi web (Web Service) da parte di altre applicazioni.


Lo stile architetturale per lo sviluppo di web service è REST (representation state transfer).
Si tratta di una serie di principi, introdotti nel 2001, che definiscono i ruoli che diversi componenti devono avere per interagire tra di loro. I sistemi RESTful si riferiscono in particolare a servizi web che implementano lo stile rest e comunicano tramite HTTP per accedere ad applicazioni web.

Si possono identificare alcuni principi che stanno alla base di una architettura RESTful:
- i **METODI** che permettono di comunicare tramite un'interfaccia uniforme
- l'**IDENTIFICAZIONE** delle risorse che ne permette l'individuazione
- la **RAPPRESENTAZIONE** delle risorse per la loro manipolazione

Va aggiunto che la comunicazione tra client e server è di tipo senza stato tra ("stateless"), cioè ogni richiesta è come se fosse la prima,, senza nessuna correlazione con le precedenti. In pratica il client deve essere in grado di mandare ogni volta al server tutte le informazioni necessarie per evadere la richiesta.


**Metodi**
Il client effettua una richiesta un web service utilizzando uno dei metodi che sono espressi come normali "verbi" HTTP, anche se, a seconda delle necessità, è possibile estendere l'interfaccia:
- **POST** - crea una risorsa e può anche modificarne lo stato. POST è una operazione di lettura e scrittura;
- **GET** - restituisci la rappresentazione della risorsa. Cat è un'operazione di sola lettura e può essere applicato ripetutamente. (idempotente) senza cambiare lo stato della risorsa;
- **PUT** - inizializza o aggiorna lo stato di una risorsa esistente;
- **DELETE** - elimina una risorsa.


**Rappresentazione**
I client interagiscono con le risorse tramite le loro "rappresentazioni" come XML e JSON. questo permette di descrivere le risorse con un alto livello di astrazione.


**Identificazione**
Perdi identificare una risorsa, i sistemi RESTful utilizzano gli URI.