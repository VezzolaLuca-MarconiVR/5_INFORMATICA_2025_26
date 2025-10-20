#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    // biforca il processo (nasce un daemon)
    int relativeID = fork(); // viene salvato un numero rappresentativo di un codice univoco relativamente a questo ambiente

    // Se questo processo è il figlio
    if (relativeID == 0)
    {
        sleep(2);
        printf("(figlio)Io sono il figlio!\n");
    }
    else
    {
        printf("(padre)Io sono il padre!\n");
        wait(NULL);
        printf("(padre)Mio figlio ha parlato!\n");
    }

    return 0;
}