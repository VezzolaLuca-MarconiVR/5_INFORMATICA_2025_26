/*
2) Prendere in input un numero intero n.
   Il processo deve creare n figli (hint: usare un ciclo for)
     - ogni figlio stampa il suo pid
     - il padre DEVE attendere la terminazione di tutti i figli
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  int n;

  do
  {
    printf("Digitare il numero di figli desiderato:");
    scanf("%d", &n);
  } while (n <= 0);

  for (int i = 0; i < n; i++)
  {
    if (fork() == 0)
    {
      printf("Sono il figlio %d e ho pid %d\n", i + 1, getpid());
      exit(0);
    }
  }

  while (wait(NULL) > 0)
    ;

  return 0;
}