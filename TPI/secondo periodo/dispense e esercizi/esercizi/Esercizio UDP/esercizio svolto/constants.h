// The expected greeting from a new client (or which already played and won)
#define GREETING_MESSAGE "salute, o mio servo"
// The code representing that the initial "greeting" is invalid
#define MSG_INCORRECT_GREETING "{E0}"
// The code representing that the message "guess" number is too big or too small
#define MSG_GUESS_OUT_OF_RANGE "{E1}"
// The code representing that the client has been registered and that it can start sending guesses
#define MSG_REGISTERED "{K0}"
// The guessed number is lower than the actual number
#define MSG_GUESS_TOO_LOW "{K1}"
// The guessed number is higher than the actual number
#define MSG_GUESS_TOO_HIGH "{K2}"
// The guessed number is equal to the actual number - "victory!"
#define MSG_GUESS_MATCHED "{K3}"
// This client has been removed from the list - access again
#define MSG_UNSUBSCRIPTED "{K4}"