#### Gruppo: | Rossato Gabriele - Poggi Federico|

#### Matricola: | 901271 - 903174 |

# Domino C

> [!NOTE]
>
> ## <b>`Compilation and Run Program`</b>
>
> - #### <strong style="color:#ed831f"> Compilation</strong>
>
>   <code style="color:#24b54b">path:</code> <code>$workspaceFolder</code> _Working Space Folder_
>
>   <code style="color:#1b8f9e"><b>command</b>:</code> <code>make</code> _Compilation with makefile_
>
> - #### <strong style="color:#edba1f">Run</strong>
>
>   <code style="color:#24b54b">path:</code> <code>$wprkspaceFolder/build</code> _Build Folder_
>
>   <code style="color:#1b8f9e"><b>command</b>:</code> <code>./dominoC</code> _Start program_

### Descrizione:

Il progetto vuole riprodurre il classico gioco del **Domino** utilizzando il linguaggio **C** standard **C99**.\
Le modalità di gioco implementate sono due:

- **Modalità standard**: il giocatore ottiene n. Tessere in mano, e ogni tessera è composta da due numeri da 1 a 6; Il gioco prevede l'inserimento delle tessere nel tavolo,con l'unica regola che la tessera da inserire, abbia almeno uno dei suoi due numeri coincidenti con almeno uno dei numeri degli estremi del tavolo.\
   Il gioco termina quando le tessere nella mano del giocatore non potranno più essere inserite o quando la mano del giocatore è vuota;

- **Modalità AI**: in questa modalità il gioco si svolge in automatico, mostrando tutte le scelte effettuate dall' AI, restituendo infine un risultato dato dalla somma di tutte le tessere presenti sul tavolo.

---

### Struttura progetto

Il progetto presenta una struttura suddivisa in più file specializzati per tipo di compito che dovranno eseguire, come per esempio il file check, è dedicato ai controlli reltivi al gioco. Ogni file contiene macro-funzioni utili a risolvere problemi semplici e distinti all'interno del gioco;\
Nel file principale "main" è presente solamente il "menu" di gioco per la scelta della modalità;

#### Strutture dati utilizzate nel gioco :

Il programma utilizza per l'identificazione della tessera un struttura contenente i suoi valori numerici,mentre per la mano e il tavolo di gioco, vengono utilizzati due array in memoria dinamica, che verrano costantemente aggiornati durante ogni fase del gioco.

#### Implementazione Modalità Standard:

Nel menu di scelta della modalità verrà domandato all'utente il numero di tessere da utilizzare, in seguito verranno distribuite le tessere al giocatore, e verra generato un tavolo vuoto, di di dimensione n ( _n=numero di tessere distribuite al giocatorte_ ).\
Successivamente il gioco verrà gestito da un "_do-while_", nel quale verrà domandato al giocatore la tessara da inserire; ad ogni scelta del giocatore verranno effettuati dei controlli per verificare la validità della tessera, e dove può essere inserita;\
Ogni controllo o mossa del giocatore viene eseguita tramite singole funzioni indipendenti.

#### Implementazione modalità AI

In questà modalità il gioco viene eseguito in autonomia, calcolando il punteggio massimo ottenibile, mostrando ogni passaggio svolto.\
Questa è simile alla modalità standard, ma differisce per diverse funzioni, il cui obbiettivo comune è di far prendere le decisioni in autonomia alla macchina.\
La logica applicata si basa sulla scelta delle tessere inseribili con frequenza maggiore e/o con il valore più alto, dato dalla somma dei due numeri.
Una volta che la tessera è stata scelta questa viene inserita n volte in base a quante volte si ripete nella mano. Infine l'iA andrà avanti in questo modo finché non raggiugnerà la fine del gioco, data dall'impossibilità di inserire altre tessere o dall'esaurimento di tessere nella mano.

---

### DIFFICOLTA' :

Essendo principianti nella programmazione con il linguaggio C, sono state riscontrate alcune difficoltà nell'ottimizzazione del codice.\
Abbiamo incontrato ulteriori difficoltà nell'organizzazione del lavoro a causa di idee divergenti riguardo all'implementazione. Pertanto, abbiamo dovuto concordare su un'idea comune che unificasse le opinioni di tutto il gruppo.

#### Strumenti utilizzati e suddivisione dei lavori:

Durante tutto lo sviluppo il team ha lavorato in presenza, ciò ha permesso uno scambio continuo di idee e la risoluzione di problematiche in maniera rapida ed efficiente, per la condivisione e l'aggiornamento del codice è stato utilizzato **GitHub**.

## _Contributors:_

`Poggi Federico:` [Poggi Federico](https://github.com/Federico-Poggi)

`Rossato Gabriele:` [Gabriele Rossato](https://github.com/GabriRoss)
