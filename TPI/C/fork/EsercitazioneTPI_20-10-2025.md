# PROCESSI PADRE/FIGLIO - fork()

1. Lanciare un processo che genera un figlio:

   - il padre stampa 'Sono il padre'
   - il figlio stampa 'Sono il figlio'
   - il padre DEVE attendere la terminazione del figlio

2. Prendere in input un numero intero n.
   Il processo deve creare n figli (hint: usare un ciclo for)

   - ogni figlio stampa il suo pid
   - il padre DEVE attendere la terminazione di tutti i figli

3. Lanciare un processo che genera due figli (A e B): - A a sua volta genera il figlio A1 - B genera i figli B1 e B2
   Ogni processo deve mostrare in output una cosa del tipo: "Sono B2, figlio di B"
   N.B.: Bisogna far terminare i processi in modo ordinato utilizzando le opportune wait()

4. a) Prendere in input un array di n interi
   Creare 2 figli: - il primo calcola e stampa la somma dei primi n/2 elementi

   - il secondo calcola e stampa la somma degli elementi restanti
   - il padre aspetta che i figli terminino

   b) utilizzare due file 'somma1.txt' e 'somma2.txt' e sfruttarli per calcolare la somma totale nel padre e output

   c) utilizzare delle pipe per permettere una 'diretta' tra padre e figlio
