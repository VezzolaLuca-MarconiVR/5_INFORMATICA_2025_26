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
La somma delle durate delle attività figlie devono corrispoondere alla durata dell'attività madre.

Il WBS si può trasformare nella OBS andando ad analizzare non più i tempi, ma le ?? (i ruoli??).

Prima colonna gli idedntificativi (1.1, 1.2, ... 2.1, 2.2, ...)
| id | descrizione | durata | (se è stato fatto il WBS)->il numero di risorse coinvolte |

#### PERT e GANTT
Il diagramma? di Pert (o critical path??) indica le dipendenze indicando il percorso critico (quello che dura di più), il quale permette di calcolare la durata dell'intero progetto.
Nel pert ci sono 4 tipologie di dipendenza: FF, FS, SF, SS.
Il diagramma di Gantt permette di visualizzare le varie fasi del progetto nella loro disposizione nel tempo ma non fornisce delle vere informazioni ulteriori??.

#### Earned Value Method
Per valutare l'andamento del progetto si può usare l'EVM (Earned Value Method). Si valuta l'avanzamento dello stato dei progetti e se esso è in linea con il piano??.
Questo metodo si basa su degli indicatori (degli indici), che vanno valutati per verificare l'andamento del progetto.
Prima comincizre un progetto, ne viene fatta una stima, sia dei costi - il "Budget Totale" (BT) -, sia dei tempi - il "Tempo Totale" (TT).
Il tempo attuale di analisi è detto "Time Now" (TN).
Il valore pianificato ("Planned Value" - PV), è la porzione di budget pianificata per il periodo corrente ("quanto avremmo dovuto spendere fino ad ora?").
Il costo attuale ("Actual Cost" - AC) è la somma dei costi reali accumulati al TN.
Il valore guadagnato ("Earned Value" - EV) è la somma dei guadagni reali accumulati al TN.

Indici:
- Il "Cost Performance Index" (CPI) è uguale a EV/AC. Se esso risulta < 1, significa che attualmente i costi sono maggiori dei guadagni;
- Lo "Schedule Performance Index" (SPI) è uguale a EV/PV. Se esso risulta < 1, significa che attualmente ??.

Parametri:
- L'"Estimate At Completion"? (EAC) è uguale a AC + (BT - EV)/CPI;
- Lo "Schedule At Completion" (SAC) è uguale al TT/SPI. Indica il tempo totale previsto secondo gli indici correnti.

### Esempio di esercizio
BT = 5'000€ (x marketing iniziale) + 100'000€ (x 3 nuovi negozi) = 105'000€
TT = 12 mesi
=========================================================
TN = 2 mesi => 16,6% del TT
PV = 5'000€ * 100% + 100'000€ *16,6% = 21'600€
AC = 6'800€ (i costi reali usati per il marketing) + 28'500 (i costi reali sostenuti fino ad ora per i negozi) = 35'300€
EV = 5'000€ + 30% * 100'000€ = 35'000€

CPI = 35'000€/35'300€ = 0,99
SPI = 35'000€/21'600€ = 1,62

EAC = 35'300€ + (105'000€ - 35'000€)/0,99 = 106'000€

SAC = 12 mesi/1,62 = 7,4 mesi