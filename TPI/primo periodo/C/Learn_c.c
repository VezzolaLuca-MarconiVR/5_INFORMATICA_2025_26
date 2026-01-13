/* learn_c.c
   Programma didattico: illustra tipi, puntatori, array, matrici, struct, allocazione.
   Commenti estesi per spiegare il perché delle scelte.
*/

#include <stdio.h>
/*

Scopo di stdio.h: input/output standard (console, file).

Funzioni principali: printf, scanf, puts, fgets, fopen, fclose, fread, fwrite, fprintf, fscanf.

Quando usarlo: ogni volta che stampi su schermo o leggi/scrivi file.

Esempio rapido:
  printf("Hello %d\n", 42);
  FILE *f = fopen("file.txt", "r");
*/
#include <stdlib.h>
/*
Scopo: utilità generali e gestione memoria dinamica; controllo del processo.

Funzioni principali: malloc, calloc, realloc, free, exit, atoi/atol, qsort, bsearch, rand/srand.

Quando usarlo: per allocare memoria, terminare programma, convertire stringhe in numeri, ordinare, generare numeri casuali.

Esempio rapido:
  int *a = malloc(n * sizeof *a);
  if (!a) exit(EXIT_FAILURE);
  free(a);
*/
#include <string.h>
/*
Scopo: operazioni su stringhe C (array di char) e su blocchi di memoria.

Funzioni principali: strlen, strcpy, strncpy, strcat, strcmp, memcpy, memmove, memset, strchr, strstr.

Quando usarlo: per manipolare stringhe NUL-terminate o copiare/muovere/azzerare blocchi di memoria.

Esempio rapido:
  char s[32];
  strcpy(s, "ciao");
  size_t len = strlen(s);
  memset(buffer, 0, size);
*/
#include <errno.h> // per strerror quando malloc fallisce

/* -------------------------
   Tipi e utilità
   ------------------------- */

/* stampare dimensioni dei tipi fondamentali per capire la piattaforma */
static void print_type_sizes(void)
{
  printf("Dimensioni tipi fondamentali (byte):\n");
  printf(" char: %zu, short: %zu, int: %zu, long: %zu, long long: %zu\n",
         sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(long long));
  printf(" float: %zu, double: %zu, _Bool: %zu\n\n",
         sizeof(float), sizeof(double), sizeof(_Bool));
}

/* -------------------------
   Vec: array dinamico di int (stile OOP minimale)
   - mostra ownership, creazione, distruzione, get/set
   ------------------------- */

typedef struct Vec
{
  size_t n;  // lunghezza
  int *data; // puntatore all'area dati
} Vec;

/* crea un Vec di n elementi inizializzati a zero
   ritorna NULL se non riesce a allocare */
Vec *vec_create(size_t n)
{
  Vec *v = malloc(sizeof *v); // allochiamo la struct
  if (!v)
    return NULL;                        // controllo fondamentale
  v->data = calloc(n, sizeof *v->data); // calloc azzera la memoria
  if (!v->data)
  { // se fallisce, liberiamo la struct e ritorniamo NULL
    free(v);
    return NULL;
  }
  v->n = n;
  return v;
}

/* libera le risorse del Vec
   - chiamare sempre quando si ha finito con l'oggetto */
void vec_free(Vec *v)
{
  if (!v)
    return; // free su NULL è sicuro ma controlliamo comunque
  free(v->data);
  free(v);
}

/* set e get con controllo dei limiti
   - ritorno 0 = successo, -1 = errore */
int vec_set(Vec *v, size_t i, int val)
{
  if (!v || i >= v->n)
    return -1;
  v->data[i] = val;
  return 0;
}
int vec_get(const Vec *v, size_t i, int *out)
{
  if (!v || i >= v->n || !out)
    return -1;
  *out = v->data[i];
  return 0;
}

/* -------------------------
   Mat: matrice contigua row-major di double
   - mostra allocazione contigua, accesso, trasposizione
   ------------------------- */

typedef struct Mat
{
  size_t r, c;  // righe e colonne
  double *data; // r*c elementi contigui, ordine row-major
} Mat;

/* crea una matrice r x c inizializzata a zero */
Mat *mat_create(size_t r, size_t c)
{
  Mat *m = malloc(sizeof *m);
  if (!m)
    return NULL;
  /* attenzione: controllare overflow della moltiplicazione r*c prima di allocare
     qui facciamo un controllo semplice: se r == 0 o c == 0 falliamo (scelta didattica) */
  if (r == 0 || c == 0)
  {
    free(m);
    return NULL;
  }
  /* usare calloc per avere memoria azzerata */
  m->data = calloc(r * c, sizeof *m->data);
  if (!m->data)
  {
    free(m);
    return NULL;
  }
  m->r = r;
  m->c = c;
  return m;
}

void mat_free(Mat *m)
{
  if (!m)
    return;
  free(m->data);
  free(m);
}

/* accesso con controllo limiti */
int mat_set(Mat *m, size_t i, size_t j, double val)
{
  if (!m || i >= m->r || j >= m->c)
    return -1;
  m->data[i * m->c + j] = val; // riga-major indexing: r*cols + c
  return 0;
}
int mat_get(const Mat *m, size_t i, size_t j, double *out)
{
  if (!m || i >= m->r || j >= m->c || !out)
    return -1;
  *out = m->data[i * m->c + j];
  return 0;
}

/* trasposta: ritorna una nuova matrice che va liberata dal chiamante */
Mat *mat_transpose(const Mat *a)
{
  if (!a)
    return NULL;
  Mat *t = mat_create(a->c, a->r);
  if (!t)
    return NULL;
  /* copia elemento per elemento */
  for (size_t i = 0; i < a->r; ++i)
  {
    for (size_t j = 0; j < a->c; ++j)
    {
      /* attenzione agli indici: elemento a[i][j] mappato in data */
      t->data[j * t->c + i] = a->data[i * a->c + j];
    }
  }
  return t;
}

/* somma di una riga: esempio di iterazione efficiente con puntatori */
double mat_row_sum(const Mat *m, size_t i)
{
  if (!m || i >= m->r)
    return 0.0;
  double s = 0.0;
  double *row = m->data + i * m->c; // punto all'inizio della riga
  for (size_t j = 0; j < m->c; ++j)
    s += row[j];
  return s;
}

/* -------------------------
   Matrice non contigua (array di righe)
   - utile per righe di lunghezza variabile, ma perde locality
   ------------------------- */

double **mat_create_rows(size_t r, size_t c)
{
  double **rows = malloc(r * sizeof *rows);
  if (!rows)
    return NULL;
  for (size_t i = 0; i < r; ++i)
  {
    rows[i] = malloc(c * sizeof *rows[i]);
    if (!rows[i])
    { // se fallisce, liberiamo le righe già allocate
      for (size_t k = 0; k < i; ++k)
        free(rows[k]);
      free(rows);
      return NULL;
    }
    /* inizializziamo a zero */
    memset(rows[i], 0, c * sizeof *rows[i]);
  }
  return rows;
}
void mat_free_rows(double **rows, size_t r)
{
  if (!rows)
    return;
  for (size_t i = 0; i < r; ++i)
    free(rows[i]);
  free(rows);
}

/* -------------------------
   Esempio in main che mostra l'uso e commenta i punti critici
   ------------------------- */

int main(void)
{
  print_type_sizes();

  /* ----- Vec demo ----- */
  Vec *v = vec_create(8);
  if (!v)
  {
    fprintf(stderr, "vec_create fallita: %s\n", strerror(errno));
    return 1;
  }
  /* impostiamo valori e dimostriamo get con controlli */
  for (size_t i = 0; i < v->n; ++i)
  {
    if (vec_set(v, i, (int)i * 3) != 0)
    {
      fprintf(stderr, "vec_set errore indice %zu\n", i);
    }
  }
  printf("Vec: ");
  for (size_t i = 0; i < v->n; ++i)
  {
    int val;
    if (vec_get(v, i, &val) == 0)
      printf("%d ", val);
  }
  printf("\n");
  /* liberiamo v quando non serve più; ownership del chiamante */
  vec_free(v);

  /* ----- Matrice contigua demo ----- */
  size_t R = 3, C = 5;
  Mat *m = mat_create(R, C);
  if (!m)
  {
    fprintf(stderr, "mat_create fallita: %s\n", strerror(errno));
    return 1;
  }

  /* riempiamo la matrice con valori calcolati */
  for (size_t i = 0; i < R; ++i)
  {
    for (size_t j = 0; j < C; ++j)
    {
      /* notare che usiamo mat_set che controlla i limiti */
      mat_set(m, i, j, (double)(i * 100 + j));
    }
  }

  printf("Matrice %zux%zu (contigua):\n", R, C);
  for (size_t i = 0; i < R; ++i)
  {
    for (size_t j = 0; j < C; ++j)
    {
      double val;
      mat_get(m, i, j, &val); // mat_get controlla i limiti
      printf("%7.1f ", val);
    }
    printf("| sum=%.1f\n", mat_row_sum(m, i));
  }

  /* trasposta: mostra come creare una nuova struttura e restituirla */
  Mat *t = mat_transpose(m);
  if (!t)
  {
    mat_free(m);
    fprintf(stderr, "traspose fallita\n");
    return 1;
  }
  printf("Trasposta %zux%zu:\n", t->r, t->c);
  for (size_t i = 0; i < t->r; ++i)
  {
    for (size_t j = 0; j < t->c; ++j)
      printf("%7.1f ", t->data[i * t->c + j]);
    printf("\n");
  }

  mat_free(t);
  mat_free(m); /* pulizia finale */

  /* ----- Matrice non contigua demo ----- */
  double **rows = mat_create_rows(R, C);
  if (!rows)
  {
    fprintf(stderr, "mat_create_rows fallita\n");
    return 1;
  }
  /* nuovo esempio: ogni riga può essere trattata indipendente */
  for (size_t i = 0; i < R; ++i)
    for (size_t j = 0; j < C; ++j)
      rows[i][j] = (double)(i * 10 + j);

  printf("Matrice non contigua:\n");
  for (size_t i = 0; i < R; ++i)
  {
    for (size_t j = 0; j < C; ++j)
      printf("%5.1f ", rows[i][j]);
    printf("\n");
  }

  mat_free_rows(rows, R);

  /* tutto pulito, terminiamo */
  return 0;
}
