#define SERVER_PORT 8888
#define GENERAL_BUFF_SIZE 128

// COMMUNICATION CODES:
// Se la stringa inviata contiene numeri o simboli: "Errore! Solo lettere ammesse. Parola resettata!" (il server cancella i progressi di quel client).
#define MSG_ERROR_BAD_STRING "{E00}"
// Se l'ennesimo invio porta la lunghezza oltre N (troppo lunga): "Troppo lunga! La lunghezza massima era [N]. Ricomincia da capo."
#define MSG_ERROR_STRING_TOO_LONG "{E02}"
// Se la stringa è valida ma la lunghezza totale è ancora inferiore al target: "Ricevuto. Parola attuale: [stringa_parziale]. Mancano [X] caratteri."
#define MSG_ERROR_STRING_TOO_SHORT "{E01}"
// Se la lunghezza totale raggiunge esattamente N: "Complimenti! Parola finale: [stringa_totale]. Sessione conclusa."
#define MSG_SESSION_SUCCESS "{SS}"

// La lunghezza massima della stringa finale
#define MAX_FINAL_STRING_LENGTH 32