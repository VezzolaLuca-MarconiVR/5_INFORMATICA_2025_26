## 17/12/2025

### VAN

Dove $I$ è l'investimento iniziale, $F_i$ è il ricavo del periodo analizzato (non per forza un anno) e $R$ è il ROI:

- $VAN = -I + \sum_{i=1}^{n} \frac{F_i}{(1+R)^i}$

### TIR

Dove $I$ è l'investimento iniziale, $F_i$ è il ricavo del periodo analizzato (non per forza un anno) e $R$ è il TIR:

- $0 = I + \sum_{i=1}^{n} \frac{F_i}{(1+R)^i}$

### Payback Period

Si somma n al ricavo del periodo (con n che parte dal valore dell'investimento - negativo - iniziale e poi al risultato della sottrazione) fino a quando non risulta un numero positivo. Il rapporto tra l'ultimo n e il ricavo del periodo è la percentuale di tempo del periodo per il cui si recupera l'investimento.

Esempio:

|                    | I     | II    | III   | IV   |
| ------------------ | ----- | ----- | ----- | ---- |
| ricavo del periodo | 2000  | 2000  | 2000  | 2000 |
| n                  | -5020 | -3020 | -1020 | 980  |
| Risultato:         | -3020 | -1020 | 980   | 2980 |

Esercizio:

- I = Investimenti iniziali
- R = Ricavo del periodo
- I = €5020
- R = €2000
- ROI = 20%
- $VAN = -5020 + \sum_{i=1}^{n} \frac {2000}{(1+0,2)^i} = 1631$

---

## 28/01/2026

### RACI

- Responsible ==> Coloro che sono direttamente coinvolti in un'attività mediante una resposabilità di ripo operativo (quelli che devono fare le cose);
- Accountable ==> Coloro che sono responsabili dell'attività perchè ne organizzano gli aspetti operativi, i quali sono appellati per prendere decisioni importanti;
- Consulted ==> Coloro che sono consultati in merito a come svolgere l'attività o riguardo alcuni dei suoi aspetti pratici;
- Informed ==> Coloro che non hanno un ruolo diretto ma che sono a conoscenza del procedimento dell'attività.

Ogni attività deve avere almeno una "R".

## 01/04/2026

### Studio di fattibilità

Un buono studio di fattibilità deve contenere:
- i tempi
- un'analisi di mercato
- uno scopo ben definito
- le risorse necessarie


### Tecnica WBS (Work Breakdown Structure)

La Work Breakdown Structure (WBS) è una tecnica di gestione progetti che scompone gerarchicamente un progetto complesso in componenti più piccole, gestibili e orientate ai risultati.
Strutturata in livelli (fasi, sottofasi, work package), facilita l'assegnazione di responsabilità, la stima dei costi e il monitoraggio del progresso.
![Esempio di WBS](./img/Tecnica%20WBS%20-%20esempio.png)

## 06/05/2026

### X Prossima Verifica

Si parte sempre dal business plan (ora si usa fare una previsione sui prossimi 3 anni).

Si identificano le macroattività:
- avviamento
- pianificazione
- sviluppo/esecuzione
- chiusura/collaudo

Utilizzando il WBS si dividono in sottoattività le macroattività qui sopra indicate.
La somma delle durate delle attività figlie deve corrispondere alla durata dell'attività madre.

Il WBS si può trasformare nella OBS (Organizational Breakdown Structure) andando ad analizzare non più i tempi, ma le responsabilità organizzative (chi è responsabile di cosa, con i relativi ruoli).

`id | descrizione | durata | (se è stato fatto il WBS) numero di risorse coinvolte`

#### PERT e GANTT
Il diagramma di PERT (Program Evaluation and Review Technique), usato insieme al metodo CPM (Critical Path Method), indica le dipendenze tra le attività e permette di identificare il percorso critico (la sequenza di attività che determina la durata minima dell'intero progetto, ovvero quella che dura di più). Calcolare il percorso critico è fondamentale perché qualsiasi ritardo su di esso si ripercuote direttamente sulla durata totale del progetto.

Nel PERT ci sono 4 tipologie di dipendenza:
- **FS** (Finish to Start): l'attività successiva inizia solo dopo che la precedente è terminata (la più comune);
- **FF** (Finish to Finish): le due attività devono terminare contemporaneamente;
- **SS** (Start to Start): le due attività devono iniziare contemporaneamente;
- **SF** (Start to Finish): l'attività successiva può terminare solo dopo che la precedente è iniziata (molto rara).

Il diagramma di Gantt permette di visualizzare le varie fasi del progetto nella loro disposizione nel tempo, ma non mostra le dipendenze tra le attività (a differenza del PERT), rendendo più difficile identificare l'impatto dei ritardi sulla durata complessiva del progetto.

#### Earned Value Method
Per valutare l'andamento del progetto si può usare l'EVM (Earned Value Method). Si valuta l'avanzamento dello stato dei progetti e se esso è in linea con il piano previsto (tempi e costi).

Questo metodo si basa su degli indicatori (degli indici), che vanno valutati per verificare l'andamento del progetto.

Prima di cominciare un progetto, ne viene fatta una stima, sia dei costi — il "Budget Totale" (BT) —, sia dei tempi — il "Tempo Totale" (TT).
Il tempo attuale di analisi è detto "Time Now" (TN).
Il valore pianificato ("Planned Value" — PV) è la porzione di budget pianificata per il periodo corrente ("quanto avremmo dovuto spendere fino ad ora?").
Il costo attuale ("Actual Cost" — AC) è la somma dei costi reali accumulati al TN.
Il valore guadagnato ("Earned Value" — EV) è il valore del lavoro effettivamente completato al TN, espresso in termini di budget (ovvero: quanto vale, in termini pianificati, ciò che è stato realmente fatto?).

**Indici:**
- Il "Cost Performance Index" (CPI) è uguale a $\frac{EV}{AC}$. Se risulta **< 1**, significa che i costi reali sono superiori al valore prodotto (si sta spendendo più del previsto); se **> 1**, si sta spendendo meno del previsto.
- Lo "Schedule Performance Index" (SPI) è uguale a $\frac{EV}{PV}$. Se risulta **< 1**, significa che il progetto è in ritardo rispetto alla pianificazione (si è prodotto meno di quanto pianificato); se **> 1**, il progetto è in anticipo.

**Parametri previsionali:**
- L'"Estimate At Completion" (EAC) è uguale a $AC+\frac{BT - EV}{CPI}$. Rappresenta la stima del costo totale finale del progetto, tenendo conto dell'efficienza di spesa attuale.
- Lo "Schedule At Completion" (SAC) è uguale a $\frac{TT}{SPI}$. Indica la durata totale prevista del progetto secondo il ritmo di avanzamento corrente.

### Esempio di esercizio
```
BT = 5.000€ (per marketing iniziale) + 100.000€ (per 3 nuovi negozi) = 105.000€
TT = 12 mesi
=========================================================
TN = 2 mesi  →  16,6% del TT

PV = 5.000€ × 100% + 100.000€ × 16,6% = 21.600€
AC = 6.800€ (costi reali marketing) + 28.500€ (costi reali negozi fino ad ora) = 35.300€
EV = 5.000€ × 100% + 100.000€ × 30% = 35.000€

CPI = 35.000€ / 35.300€ ≈ 0,99  →  costi leggermente superiori al valore prodotto
SPI = 35.000€ / 21.600€ ≈ 1,62  →  progetto in anticipo rispetto ai tempi

EAC = 35.300€ + (105.000€ - 35.000€) / 0,99 ≈ 106.000€
SAC = 12 mesi / 1,62 ≈ 7,4 mesi
```