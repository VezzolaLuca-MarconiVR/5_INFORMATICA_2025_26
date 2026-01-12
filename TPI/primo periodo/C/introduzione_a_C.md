stdbool.h ==> library for bool data type and true/false values

### Tipi primitivi

- **Tipi**: `char`, `short`, `int`, `long`, `long long`, `float`, `double`, `_Bool`.
- **Dimensione**: dipende dalla piattaforma; usa `sizeof` per verificare.
- **Signed/Unsigned**: `unsigned` rimuove segno, attenzione alle promozioni e confronti con signed.
- **Costanti**: preferisci `static const` a macro non tipate.
- **Promozioni**: tipi piccoli promossi a `int` nelle espressioni; attenzione a conversioni implicite (overflow).

Confronto Java: Java ha tipi a dimensione fissa e garbage collection; in C devi gestire dimensioni, segni e overflow manualmente.

---

### Puntatori e riferimenti

- **Concetto**: un puntatore è un valore che contiene un indirizzo di memoria. Non è un oggetto come in Java, è pura aritmetica di indirizzi.
- **Dichiarazione**: `T *p` puntatore a T; `T **pp` puntatore a puntatore.
- **Dereferenza**: `*p` legge/scrive l'oggetto puntato. Usa `&x` per ottenere indirizzo.
- **Null**: `NULL` o `0`; sempre verificare prima di dereferenziare.
- **Pointer arithmetic**: `p + n` avanza di `n * sizeof(*p)`. `p[i]` ≡ `*(p + i)`.
- **Const correctness**:
  - `const T *p` dato immutabile tramite p.
  - `T * const p` puntatore immutabile.
  - `const T * const p` entrambe immutabili.
- **Funzione vs metodo**: le funzioni non hanno this; simula metodi passando `struct* self`.
- **Funzioni callback**: `R (*f)(A,B)`.

Per chi viene da Java: i riferimenti Java sono sicuri e non consentono aritmetica; in C i puntatori possono leggere qualsiasi indirizzo valido, causare UB o crash se usati male. Tratta i puntatori come risorse da documentare e validare.

Errori frequenti:

- Dereferenziare NULL.
- Uso-after-free.
- Aliasing e violazione strict-aliasing (non castare arbitrariamente, usare `char*` per view byte).
- Confondere `sizeof(p)` con `sizeof(*p)`.

---

### Array e matrici


- **Array statici**: `T a[N];` allocati nello scope (stack se non `static`). `sizeof(a)/sizeof(a[0])` funziona solo nello stesso scope.
- **Decay**: quando passi `a` a funzione diventa `T*` e perdi la lunghezza; passa sempre `size_t n` separato.
- **2D statico**: `T m[R][C];` memoria contigua, ordine row-major.
- **2D dinamico contiguo**: allocare un singolo blocco `T *m = malloc(R * C * sizeof *m);` usa indice `m[r*C + c]`. Preferito per cache locality. [Attenzione! "r" e "c" sono gli indici - partendo da 0 - della riga e della colonna alla quale si vuole accedere]
- **2D dinamico a righe**: `T** rows = malloc(R * sizeof *rows);` poi ogni `rows[i] = malloc(C * sizeof *rows[i]);` non è contiguo, comodo per righe variabili ma peggiore per prestazioni.
- **Bounds**: C NON controlla limiti; mantieni e passa sempre le dimensioni.

Confronto Java:

- In Java `new int[R][C]` crea array di array; in C puoi scegliere contiguo o array di puntatori; preferisci contiguo per prestazioni.

Esempio accesso contiguo:

```c
double *mat = malloc(R * C * sizeof *mat);
// [Attenzione! "r" e "c" sono gli indici - partendo da 0 - della riga e della colonna alla quale si vuole accedere - e.g. il primo elemento è a r=0 e c=0]
double at(double *m, size_t r, size_t c, size_t C) { return m[r*C + c]; }
```

---

### Allocazione e gestione memoria

#### Guarda qui: https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

- **Allocazione**: `malloc`, `calloc`, `realloc`. Controlla sempre il risultato.
- **Deallocazione**: `free`. Ogni `malloc`/`calloc`/`realloc` deve avere un `free` deterministico.
- **Ownership**: documenta chi è responsabile del `free`. API chiara: chi alloca libera.
- **Realloc**: usare un puntatore temporaneo:

```c
void *tmp = realloc(p, new_size);
if (!tmp) { /* gestire errore, p ancora valido */ } else p = tmp;
```

- **Zeroing**: `calloc` o `memset` dopo `malloc`.
- **Errori comuni**: memory leak, use-after-free, double-free, buffer overflow.
- **Strumenti**: sanitizers (`-fsanitize=address,undefined`), valgrind, compiler warnings.

Confronto Java: non esiste garbage collector automatico in C; la gestione è manuale e deve essere progettata come parte dell'API.

---

### Struct, funzioni e buone pratiche

- **Struct**:
  - Dichiarazione: `struct S { int a; double b; };`
  - Ordinare campi per ridurre padding.
  - Usare puntatori a struct per passare per riferimento e ridurre copie.
  - Flexible array member: `struct X { size_t n; int v[]; };` allocare con spazio extra per `v`.
- **API e proprietà**:
  - Documenta nullabilità, ownership e condizioni di errore.
  - Usa nomi chiari `create_X`, `destroy_X`, `X_init`, `X_free`.
- **Funzioni**:
  - Metodi: simulali con `void X_do(struct X *self, ...)`.
  - Prototipi in header, definizioni in .c.
  - `static` per funzioni private al file.
- **Error handling**:
  - Valori di ritorno (0 ok, <0 errore) o `NULL` per allocazioni.
  - `errno` per errori di sistema; non usarlo come unica API di libreria.
- **Const e tipi opachi**:
  - Esporta solo `typedef struct X X;` e fornisci funzioni; permette incapsulamento come in Java.

Esempi minimi

```c
// header.h
typedef struct Vec Vec;
Vec *vec_create(size_t n);
void vec_free(Vec *v);
int vec_set(Vec *v, size_t i, int val);

// impl.c
struct Vec { size_t n; int *data; };
Vec *vec_create(size_t n) {
  Vec *v = malloc(sizeof *v);
  if (!v) return NULL;
  v->data = calloc(n, sizeof *v->data);
  if (!v->data) { free(v); return NULL; }
  v->n = n;
  return v;
}
```

---

### Checklist rapido

- **Compilare** con warning: `-Wall -Wextra -Wpedantic -std=c11`.
- **Controllare** ogni `malloc/realloc`.
- **Documentare** ownership e nullabilità.
- **Preferire** memoria contigua per matrici per prestazioni.
- **Usare** `sizeof *p` quando allochi per evitare errori di tipo.
- **Evitare** aritmetica su puntatori non validi.
- **Testare** casi limite e usare sanitizers.

---
