#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// STRUTTURE SI CREANO QUI PER EVITARE CONFLITTI CON FUNZIONI
typedef struct
{
    int num1;
    int num2;
} tessera;

//----------------------FUNZIONI FIRME---------------------------//
void style();
void error(const char *message);
tessera *stdTessere();
tessera *creaTable(int numberOfTesser);
void printTessere(tessera *a, int size);
void printTessereTable(tessera *a, int size);
tessera *giveTessereToPlayer(tessera *tessere, int nTessere);
int chooseCard(tessera *playercards);
void rotate(tessera *playerCards1, int i);
void pushHead(tessera *table, tessera *playerCards1, int choice, int *pointer);
void pushFooter(tessera *table, int size, tessera *playerCards1, int choice, int *pointer);
int insertCheck(tessera *table, tessera *playercards, int pointer, int choice);
int checkAfterRotate(tessera *table, tessera *playercards, int pointer, int choice);
tessera *newPlayercards(tessera *playercards, int size, int choice);
int playMode();
bool checkIfGameCanContinue(tessera *currentGameTable, int sizeTable, tessera *playerCards1, int playerCardSize);

void mod1(tessera *std, int numberOfcards);

//---------------------------------------------------------------//

// FUNZIONE PER GRAFICA E STILE
void style()
{
    for (char k = 0; k <= 119; ++k)
    {
        printf("-");
    }
    puts(" ");
};

// STAMPA ERRORE
void error(const char *message)
{
    printf("ERRORE: %s", message);
};

// GENERA TESSERE STANDARD
tessera *stdTessere()
{
    const int lunghezza = 21;
    const int maxValue = 6;
    // STD NOME UNIVOCO PER NON FARE CONFUSIONE
    // EQUIVALENTE CODICE ---> tessera std[21];
    tessera *std = (tessera *)malloc(sizeof(tessera) * lunghezza);
    if (std == NULL)
    {
        // GESTIONE ERRORE ALLOCAZAIONE
        error("Errore di allocazione di memoria");
        // GESTIONE ERRORE ALLOCAZIONE
        exit(EXIT_FAILURE);
    }
    // INIZIALIZZAZIONE TUTTE 21 TESSERE BASE/STANDARD (str)
    int i = 0;
    // DISEGNO GABRI WHATSAPP
    for (int n1 = 1; n1 <= maxValue; ++n1)
    {
        // N1 PARTENZA PRIMO NUMERO ARRAY
        for (int n2 = n1; n2 <= maxValue; ++n2)
        {
            // N2 PARTE DAL VALORE DI N1
            std[i].num1 = n1;
            std[i++].num2 = n2;
        }
    }
    return std;
}

// TAVOLO DA GIOCO
tessera *creaTable(int numberOfTesser)
{
    tessera *table = (tessera *)malloc(sizeof(tessera) * numberOfTesser);
    return table;
}

// STAMPA TAVOLO
void printTessereTable(tessera *a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (a[i].num1 != 0) // La condizione fa in modo che la funzione stampi solo le tessere che hanno un valore diverso da 0
        // E' sufficiente che solo uno tra num1  e num2 siano diversi da 0 dal momento che è impossibile avere tessere del gioco composte da un valore uguale a 0
        {
            printf("[%d|%d] ", a[i].num1, a[i].num2);
        }
    }
    puts("");
}

// STAMPA TESSERE
void printTessere(tessera *a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("[%d|%d] ", a[i].num1, a[i].num2);
    }
    puts("");
}

// FUNZIONE PER DISTRIBUIRE LE TESSERE IN BASE AL NUMERO PASSATO DI TESSERE VOLUTE IN MANO DEL GIOCATORE TUTTO CASUALE!!!!
tessera *giveTessereToPlayer(tessera *tessere, int nTessere)
{
    tessera *palyerCards = (tessera *)malloc(sizeof(tessera) * nTessere);

    int randNumberForCycleTheCards;
    for (int i = 0; i < nTessere; ++i)
    {
        randNumberForCycleTheCards = rand() % 21;
        palyerCards[i].num1 = tessere[randNumberForCycleTheCards].num1;
        palyerCards[i].num2 = tessere[randNumberForCycleTheCards].num2;
    }

    return palyerCards;
}

// SCELTA TESSERA MANO GIOCATORE
int chooseCard(tessera *playercards)
{
    int indice = 0;
    bool verifica = true;
    while (verifica)
    {
        printf("%s\n%s", "Quale tessera vuoi giocare?",
               "Scegliere un numero da 1 a 28: ");
        scanf("%d", &indice);
        if (indice <= 28 && indice >= 1)
        {
        }
        verifica = false;
    }
    indice -= 1;
    return indice;
}

// FUNZIONE PER RUOTARE UNA TESSERA
void rotate(tessera *playerCards1, int i)
{
    int temp = playerCards1[i].num1; // variabile temporanea salvata per lo swap
    playerCards1[i].num1 = playerCards1[i].num2;
    playerCards1[i].num2 = temp;
}

// PUSH HEAD TESSERA
void pushHead(tessera *table, tessera *playerCards1, int choice, int *pointer)
{
    table[*pointer] = playerCards1[choice];
    *pointer += 1; // VARIFICA CHE QUANDO PUNTA ALL' ELEMENTO 29 NON SIA POSSIBILE INSERIRE O ESSERCI LATRO (OUT OF ARRAY)
}

// PUSH FOOTER TESSERA
void pushFooter(tessera *table, int size, tessera *playerCards1, int choice, int *pointer)
{
    for (size_t i = size - 1; i > 0; i--)
    {
        table[i] = table[i - 1];
    }
    table[0] = playerCards1[choice];
    *pointer += 1;
}

// Controllo proseguimento partita
bool checkIfGameCanContinue(tessera *currentGameTable, int sizeTable, tessera *playerCards1, int playerCardSize)
{
    // Quantità elementi dentro al tavolo(Grandezza array)
    // Controllo mosse disponibili
    int leftmostLeftNumber = currentGameTable[0].num1;
    int mostRightNumber;
    if (playerCards1 == 0)
    {
        return false;
    }
    else
    {
        for (size_t i = 0; i < sizeTable; i++)
        {
            if (i = sizeTable - 1)
            {
                mostRightNumber = currentGameTable[i].num2;
            }
            for (size_t i = 0; i < playerCardSize; i++)
            {
                int num1 = playerCards1[i].num1;
                int num2 = playerCards1[i].num2;
                if (num1 == mostRightNumber || num2 == mostRightNumber)
                {
                    return true;
                }
                else if (num1 == leftmostLeftNumber || num2 == leftmostLeftNumber)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return false;
}

// CONTROLLO COMPATIBILITA' PRIMA DELL'INSERIMENTO

int lastInsterCheck(tessera *table, tessera *playercards, int pointer, int choice)
{
    int left = table[0].num1;            // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio
    if (left == 0 && right == 0)
        return 1;
    if (right == playercards[choice].num1)
        return 1;
    if (left == playercards[choice].num2)
        return 2;
    else
        return -1;
}

// CONTROLLO COMPATIBILITA' TESSERE DOPO LA ROTAZIONE
int checkAfterRotate(tessera *table, tessera *playercards, int pointer, int choice)
{
    int left = table[0].num1;            // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio
    /*for(size_t i = 0; i < dimTable; i++){ // Qualora si volesse usare questo metodo bisogna inserire la dimensione del tavlo
        if(table[i].num2 == 0){
            right = table[i - 1].num2;
            break;
        }
    }*/
    if (left == 0 && right == 0)
        return 1;
    if ((left == playercards[choice].num2) || (right == playercards[choice].num1))
        return 1;
    else
        return -1;
}

// CONTROLLO COMPATIBILITA' TESSERE
int insertCheck(tessera *table, tessera *playercards, int pointer, int choice)
{
    int left = table[0].num1;            // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio (Passaggio variabile pointer per valore e non per riferimento per non modificare il valore del puntatore)
    /*for(size_t i = 0; i < dimTable; i++) // Primo metodo con scorrimento dell'array
        if(table[i].num2 == 0){
            right = table[i - 1].num2;
            break;
        }
    }*/

    printf("%d", left);
    printf("%d", right);
    if (left == 0 && right == 0)
        return 1;
    if ((left == playercards[choice].num1) || (left == playercards[choice].num2) || (right == playercards[choice].num1) || right == (playercards[choice].num2))
        return 1;
    else
        return -1;
}

// RIDUZIONE ARRAY
tessera *newPlayercards(tessera *playercards, int size, int choice)
{
    tessera *new = (tessera *)malloc(sizeof(tessera) * (size - 1)); // Controllo NULL!!
    if (new == NULL)
    {
        // GESTIONE ERRORE ALLOCAZAIONE
        error("Errore di allocazione di memoria");
        // GESTIONE ERRORE ALLOCAZIONE
        exit(EXIT_FAILURE);
    } // errore allocazione memoria

    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != choice)
        {
            new[j++] = playercards[i];
        }
    }

    free(playercards);
    return new;
}

int main()
{
    // SEME NUMERI RANDOMICI
    srand(time(NULL));

    // VARIABILI MAIN
    tessera *std = stdTessere();
    bool playAgain = true;
    bool changeResp = true;
    int risposta = 0;
    int numberOfcards = 28;

    // INTRODUZIONE
    style();
    printf("\nBENVENUTO IN DOMINO\n\n");
    style();
    while (playAgain)
    {
        puts("");
        int modalita = playMode();
        style();
        switch (modalita)
        {
        case 1:
            printf("Modalità: %d\n", modalita);
            mod1(std, numberOfcards);
            break;
        case 2:
            printf("Modalità: %d\n", modalita);
            break;
        case 3:
            printf("Modalità: %d\n", modalita);
            break;
        default:
            error("Modalità non valida\n");
        }
        // Possibilità di giocare nuovamente
        do
        {
            style();
            printf("\nVuoi giocare ancora?\n\n1: Si\n2: No\n\nHai scelto l'opzione: ");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                changeResp = false;
                puts("");
                style();
                break;
            case 2:
                changeResp = false;
                playAgain = false;
                break;
            default:
                error("Comando non valido. Scegli tra le opzioni disponibili.\n\n");
                ;
            }
        } while (changeResp);
    }
    puts("");
    style();

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(std);
    // FINE GIOCO
    return 0;
}

// MODALITA' DI GIOCO
int playMode()
{
    int mod = 0;
    printf("Inserisci la modalita di gioco:");
    puts("\n");
    printf("1: Modalità classica interattiva\n2: Modalità AI\n3:");
    puts("\n");
    printf("Inserisci il numero della modalità desiderata [1, 2, 3]: ");
    do
    {

        scanf("%d", &mod);
        // ERRORE MODALITA';
        if (mod > 3 || mod < 0)
        {
            puts(" ");
            // printf("Modalità inserita non valida!\n");
            error("Modalità inserita non valida! \n");
            printf("Inserisci una modalità valida [1, 2, 3]: ");
        };

    } while (mod > 3 || mod < 0);
    puts(" ");
    // printf("Sono uscito");
    return mod;
};

// MODALITA' CLASSICA
void mod1(tessera *std, int numberOfcards)
{
    // VARIABILI MODALITA' 1
    bool stateOfgame = true;                   // VARIABILE CONTROLLO STATO DI GIOCO (VERO: GIOCO CONTINUA; FALSO: GAME OVER)
    int pointer = 0;                           // PUNTATORE ULTIMA TESSERA INSERITA ARRAY
    int rotateQ = 0;                           // VARIABILE ROTAZIONE TESSERA
    int choice = 0;                            // INDICE TESSERA SELEZIONATA
    int compatibilyCheck = 0;                  // VARIABILE CONTROLLO COMPATIBILITA' INSERIMENTO TESSERE, COMPATIBILIA' TRA MANO E TAVOLO
    int compatibilyCheckAfteRotate = 0;        // VARIABILE COMPATIBILITA' TESSERE DOPO LA ROTAZIONE
    int lastCompatibilyCheck = 0;              // VARIABLIE ULTIMO CONTROLLO PRIMA DELL'INSERIMENTO
    tessera *table = creaTable(numberOfcards); // CREAZIONE TAVOLO DA GIOCO

    printf("Tessere nella tua mano :"); // INTESTAZIONE
    puts("\n");

    tessera *playerCards1 = giveTessereToPlayer(std, numberOfcards); // DISTRIBUIZIONE TESSERE MANO GIOCATORE

    do
    {
        do
        {

            printTessere(playerCards1, numberOfcards); // STAMPA TESSERE MANO GIOCATORE
            puts("\n");

            choice = chooseCard(playerCards1); // ASSEGNA A CHOICE L'INDICE DELLA TESSERA SELEZIONATA
            printf("[%d|%d] ", playerCards1[choice].num1, playerCards1[choice].num2);

            puts(" ");
            compatibilyCheck = insertCheck(table, playerCards1, pointer, choice);
            printf("%d", compatibilyCheck);
            puts(" ");
            printf("IL PUNTATORE %d", pointer);
            puts(" ");

            if (compatibilyCheck == -1)
            {
                error("Non è possibile inserire la tessera selezionata! Scegli un'altra tessera");
                puts(" ");
            }

        } while (compatibilyCheck == -1); // CONTROLLO COMPATIBILITA' 1

        do
        {
            puts("\nVuoi ruotare la tessera selezionata?\n\n1-Si, ruotala\n2-No, lasciala così");
            do
            {
                printf("Hai scelto l'opzione: ");
                scanf("%d", &rotateQ);
                if (rotateQ < 1 || rotateQ > 2)
                {
                    error("Comando non valido. Scegli tra le opzioni disponibili.\n");
                }
            } while (rotateQ < 1 || rotateQ > 2);

            if (rotateQ == 1)
            {
                rotate(playerCards1, choice);
            }
            printf("[%d|%d]\n\n", playerCards1[choice].num1, playerCards1[choice].num2);

            puts(" ");
            compatibilyCheckAfteRotate = checkAfterRotate(table, playerCards1, numberOfcards, choice);
            printf("%d", compatibilyCheckAfteRotate);
            puts(" ");

            if (compatibilyCheckAfteRotate == -1)
            {
                error("Devi ruotare la tessera selezionata nel verso corretto!"); // Errore rotazione tessera
            }
        } while (compatibilyCheckAfteRotate == -1); // CONTROLLO COMPATIBILITA' 2

        do
        {
            int pushSide = 0; // Variabile per memorizzare la scelta della posizione di inserimento della tessera nel tavolo da gioco
            printf("%s\n%s\n", "Per inserire la tessera in coda, inserire 1;",
                   "Per inserire la tessera in testa, inserire 2;");
            scanf("%d", &pushSide);

            lastCompatibilyCheck = lastInsterCheck(table, playerCards1, pointer, choice);
            // Controllo corretti inserimento tessera, quindi controllo tra num1
            if (pushSide == 1) // Posizionamento in coda
            {
                if (lastCompatibilyCheck == 1)
                {
                    pushHead(table, playerCards1, choice, &pointer);
                    printTessereTable(table, numberOfcards);
                    printf("\n%d\n", pointer);
                }
                else
                {
                    error("Svegliati!!");
                }
            }

            if (pushSide == 2)
            { // Posizionamento in testa
                if (lastCompatibilyCheck == 2)
                {
                    pushFooter(table, numberOfcards, playerCards1, choice, &pointer);
                    printTessereTable(table, numberOfcards);
                    printf("\n%d\n", pointer);
                }
                else
                {
                    error("Svegliati!!");
                }
            }
        } while (lastCompatibilyCheck == -1);

        // RIDIMENSIONAMENTO ARRAY
        playerCards1 = newPlayercards(playerCards1, numberOfcards, choice);
        numberOfcards--;
        // printTessere(table, numberOfcards);

        puts("\n");
    } while (stateOfgame == true);

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!

    free(table);
    free(playerCards1);
}
