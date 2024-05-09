#### Gruppo: | Rossato Gabriele - Poggi Federico - Praticò Federico - Pozzato Elia |

# Domino C

> [!NOTE]
>
> ## <b>`Compilation and Run Program`</b>
>
> - #### <strong style="color:#ed831f"> Compilation</strong>
>
>   <code style="color:#24b54b">path:</code> <code>$wprkspaceFolder</code> _Working Space Folder_
>
>   <code style="color:#1b8f9e"><b>command</b>:</code> <code>make</code> _Compilation with makefile_
>
> - #### <strong style="color:#edba1f">Run</strong>
>
>   <code style="color:#24b54b">path:</code> <code>$wprkspaceFolder/build</code> _Build Folder_
>
>   <code style="color:#1b8f9e"><b>command</b>:</code> <code>run</code> _Start program_

### Descrizione:

Il progetto vuole riprodurre il classico gioco del **Domino** utilizzando il linguaggio **C** standard **C99**.\
Le modalità di gioco implementate sono due:

- **Modalità standard**: il giocatore ottiene n. Tessere in mano, e ogni tessera è composta da due numeri da 1 a 6; Il gioco prevede l'inserimento delle tessere nel tavolo,con l'unica regola che la tessera da inserire, abbia almeno uno dei suoi due numeri coincidenti con almeno uno dei numeri degli estremi del tavolo.\
   Il gioco termina quando le tessere nella mano del giocatore non potranno più essere inserite o quando la mano del giocatore è vuota;

- **Modalità AI**: in questa modalità il gioco si svolge in automatico, mostrando tutte le scelte effettuate dall' AI, restituendo infine un risultato dato dalla somma di tutte le tessere presenti sul tavolo.
