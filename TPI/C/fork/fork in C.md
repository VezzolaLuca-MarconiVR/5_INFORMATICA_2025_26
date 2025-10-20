# I Fork in C

## Cos'è un fork?

Un fork è la duplicazione di un processo con il fine di dividerlo in due processi distinti.

## Come si fa in C?

La funzione `fork()` ritorna al padre il pid del figlio appena creato e al figlio invece ritorna 0.

Esempio:

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    // biforca il processo (nasce un daemon)
    int relativeID = fork(); // viene salvato un numero rappresentativo di un codice univoco relativamente a questo ambiente

    // Se questo processo è il figlio
    if (relativeID == 0)
    {
        printf("Io sono il figlio! Il mio pid è %d\n", getpid());
        printf("Sono il figlio e ho come id relativo %d\n", relativeID);
    }
    else
    {
        printf("Io sono il padre! Il mio pid è %d\n", getpid());
        printf("Sono il padre e ho come id relativo %d\n", relativeID);
    }

    return 0;
}
```

## Casi particolari:

### Desincronizzazione tra padre e figlio

La desincronizzazione accade quando padre e figlio eseguono in modo indipendente e non c'è alcuna sincronizzazione tra di loro: l'ordine di esecuzione non è garantito. Spesso il padre può terminare o proseguire prima che il figlio abbia completato il suo lavoro.

Esempio minimo (nessuna sincronizzazione):

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // figlio
        sleep(2); // simula lavoro più lungo
        printf("Figlio: pid=%d, ppid=%d\n", getpid(), getppid());
    } else { // padre
        printf("Padre: pid=%d, figlio=%d\n", getpid(), pid);
        // non aspetta il figlio -> desincronizzazione
    }

    return 0;
}
```

Se vuoi che il padre aspetti il figlio e quindi sincronizzare l'ordine, usa `wait()` o `waitpid()` nel padre:

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) { // figlio
        sleep(2);
        printf("Figlio: pid=%d\n", getpid());
    } else { // padre
        int status;
        waitpid(pid, &status, 0); // sincronizza: aspetta la terminazione del figlio
        printf("Padre: figlio %d terminato\n", pid);
    }

    return 0;
}
```

### Processi Orfani

Un processo orfano si verifica quando il processo padre termina prima del figlio. Il figlio non rimane senza controllo: il sistema operativo riassegna il figlio a un processo di sistema (tipicamente `init` o `systemd`) che si occuperà di adottarlo.

Esempio di processo orfano (il padre termina subito):

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // figlio
        sleep(2);
        printf("Figlio: pid=%d, ppid=%d\n", getpid(), getppid());
        // quando il padre è terminato, getppid() probabilmente sarà 1 (init/systemd)
    } else { // padre
        printf("Padre: esco subito (pid=%d)\n", getpid());
        exit(0); // il padre termina, il figlio diventa orfano
    }

    return 0;
}
```

Nota: il comportamento visibile (ad es. `ppid` che diventa 1) dipende dal sistema, ma il concetto di adozione è standard.

### Processi Zombie

Un processo zombie (defunct) è un processo figlio che ha terminato l'esecuzione ma il padre non ha ancora chiamato `wait()`/`waitpid()` per leggerne lo stato di terminazione. Il processo zombie mantiene una voce nella tabella dei processi finché non viene "rimosso" dal padre.

Esempio che genera uno zombie (padre non richiama wait):

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // figlio
        printf("Figlio: termino subito (pid=%d)\n", getpid());
        _exit(0); // termina subito
    } else { // padre
        printf("Padre: non chiamo wait, dormo 10 secondi (pid=%d)\n", getpid());
        sleep(10); // durante questo tempo il figlio resta zombie
        printf("Padre: torno, ora posso chiamare wait per rimuovere lo zombie\n");
        // se non si chiama wait, la voce zombie rimane finché il padre non termina
    }

    return 0;
}
```

Come evitare zombie:

- Il padre dovrebbe chiamare `wait()` o `waitpid()` per raccogliere lo stato dei figli terminati.
- In programmi server o daemon usare un gestore del segnale `SIGCHLD` per chiamare `waitpid(..., WNOHANG)` e raccogliere tutti i figli terminati.

Esempio rapido di gestione non bloccante in un handler per SIGCHLD:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signo) {
    // raccogli tutti i figli terminati senza bloccare
    while (waitpid(-1, NULL, WNOHANG) > 0) { }
}

int main(void) {
    signal(SIGCHLD, sigchld_handler);
    // ... codice che crea figli con fork() ...
    return 0;
}
```

Queste tre categorie (desincronizzazione, orfani e zombie) coprono i casi pratici più comuni quando si lavora con `fork()` e la gestione dei processi figlio.
