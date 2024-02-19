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
tessera *creaTable(int numberOfcards);
void printTessere(tessera *a, int size);
void printTessereTable(tessera *a, int size);
tessera *giveTessereToPlayer(tessera *tessere, int nTessere);
int chooseCard(tessera *playercards);
void rotate(tessera *playerCards1, int i);
void pushHead(tessera *table, tessera *playerCards1, int choice, int *pointer);
void pushFooter(tessera *table,int size, tessera *playerCards1, int choice, int *pointer);
int insertCheck(tessera *table, tessera *playercards, int pointer, int choice);
int checkAfterRotate (tessera *table, tessera *playercards, int pointer, int choice);
tessera *newPlayercards(tessera *playercards, int size, int choice);
int playMode();
void mod1(tessera *std, int numberOfcards);
void mossa(tessera *table, tessera *playerCards1, int *indexTable, int *numberOfcards, int *choiceptr, int mossa1, int tableSize);
//void mossa1(tessera *table, tessera *playerCards1, int *indexTable, int *numberOfcards);
//---------------------------------------------------------------//

// FUNZIONE PER GRAFICA E STILE
void style()
{
    for (char k = 0; k <= 90; ++k)
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

//GENERA TESSERE STANDARD
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

//STAMPA TAVOLO 
void printTessereTable(tessera *a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if(a[i].num1 != 0) // La condizione fa in modo che la funzione stampi solo le tessere che hanno un valore diverso da 0
        // E' sufficiente che solo uno tra num1  e num2 siano diversi da 0 dal momento che è impossibile avere tessere del gioco composte da un valore uguale a 0
        {
        printf("[%d|%d] ", a[i].num1, a[i].num2);
        }
    }
    puts("");
}

//STAMPA TESSERE
void printTessere(tessera *a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if ((a[i].num1 != 0) && (a[i].num2 != 0)) {
            if (i == (size/2)) puts("");
            printf("[%d|%d] ", a[i].num1, a[i].num2);
        }
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

//SCELTA TESSERA MANO GIOCATORE (NO AI)
int chooseCard(tessera *playercards)
{
    int indice = 0;
    bool verifica = true;
    while(verifica){
        printf("%s\n%s", "Quale tessera vuoi giocare?",
                         "Scegliere un numero da 1 a 28: ");
        scanf("%d", &indice);
        if(indice <= 28 && indice >= 1) verifica = false;
        else 
        {
            puts("");
            error("Comando non valido. Scegli tra le opzioni disponibili.\n\n");
        }
    }
    indice -= 1;
    return indice;
}

// FUNZIONE PER RUOTARE UNA TESSERA
void rotate(tessera *playerCards1, int i)
{
    int temp = playerCards1[i].num1; //variabile temporanea salvata per lo swap
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
    for(size_t i = size - 1; i > 0; i--){ 
         table[i] = table[i - 1];
    }
    table[0] = playerCards1[choice];
    *pointer+=1;
}

// CONTROLLO COMPATIBILITA' TESSERE
int insertCheck(tessera *table, tessera *playercards, int dimTable, int choice)
{
    int left = table[0].num1; // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio
    if(left == 0 && right == 0) return 1;
    if(right == playercards[choice].num1) return 1;
    if(left == playercards[choice].num2) return 2;
    else return -1; 
}

// CONTROLLO COMPATIBILITA' TESSERE DOPO LA ROTAZIONE
int checkAfterRotate (tessera *table, tessera *playercards, int pointer, int choice)
{
    int left = table[0].num1; // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio
    /*for(size_t i = 0; i < dimTable; i++){ // Qualora si volesse usare questo metodo bisogna inserire la dimensione del tavlo
        if(table[i].num2 == 0){
            right = table[i - 1].num2; 
            break;
        }
    }*/
    if(left == 0 && right == 0) return 1;
    if((left == playercards[choice].num2) || (right == playercards[choice].num1)) return 1;
    else return -1;
}

// CONTROLLO COMPATIBILITA' TESSERE
int insertCheck(tessera *table, tessera *playercards, int pointer, int choice)
{
    int left = table[0].num1; // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = table[pointer - 1].num2; // Variabile per il salvataggio (Passaggio variabile pointer per valore e non per riferimento per non modificare il valore del puntatore)
    /*for(size_t i = 0; i < dimTable; i++) // Primo metodo con scorrimento dell'array
        if(table[i].num2 == 0){
            right = table[i - 1].num2; 
            break;
        }
    }*/

    printf("%d", left);
    printf("%d", right);
    if(left == 0 && right == 0) return 1;
    if((left == playercards[choice].num1) || (left == playercards[choice].num2) || (right == playercards[choice].num1) || right == (playercards[choice].num2)) return 1;
    else return -1;
}

// RIDUZIONE ARRAY 
tessera *newPlayercards(tessera *playerCards1, int size, int choice)
{
    // CREAZIONE NUOVA MEMEORIA
    tessera *new = (tessera *)malloc(sizeof(tessera) * (size - 1)); // RIDUCI FUORI DALLA FUNZIONE LA DIMENSIONE DELLA MANO
    if (new == NULL)
    {
        // GESTIONE ERRORE ALLOCAZAIONE
        error("Errore di allocazione di memoria");
        // GESTIONE ERRORE ALLOCAZIONE
        exit(EXIT_FAILURE);
    } //errore allocazione memoria

    // INIZIALIZZO NEW
    int j = 0;
    for (int i = 0; i < size; i++) {
        if (i != choice) {
            new[j++] = playerCards1[i];
        }
    }

    // SALVO INDIRIZZO VECCHIA MALLOC PER LIBERARLA
    tessera *vecchioArray = playerCards1; //free contiene indirizzo vecchio array;

    /*
    // CONTROLLI INDIRIZZI MEMEORIA
    printf("playerCards1 inziale: %p\n", playerCards1);
    printf("vecchioArray = playerCards1 e inziale: %p\n", vecchioArray);
    printf("new: %p\n\n", new);
    */

    // FREE MALLOC INDIRIZZO VECCHIO 0x7f017e8973e0
    free(vecchioArray);

    // printf("librerata vecchia mallocc. %d\n", vecchioArray[1].num2);
return new; // NUOVO INDIRIZZO CONTENTE NUOVA MALLOC 0x5598feb00d50
}

// FUNZIONE MADRE GIOCO 
int main()
{
    // SEME NUMERI RANDOMICI
    srand(time(NULL));

    //VARIABILI ITERAZIONE MAIN
    bool playAgain = true;
    bool changeResp = true;
    // VARIABILI GIOCO MAIN
    tessera *std = stdTessere();
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
            printf("\nModalità: %d\n", modalita);
            mod1(std, numberOfcards);
            break;
        case 2:
            printf("\nModalità: %d\n", modalita);
            break;
        case 3:
            printf("\nModalità: %d\n", modalita);
            break;
        default:
            error("Modalità non valida\n");
        }
        // Possibilità di giocare nuovamente
        do
        {   
            //style();
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
                error("Comando non valido. Scegli tra le opzioni disponibili.\n\n");;
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

// MODALITA' DI GIOCO MENU'
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

// MODALITA' CLASSICA 1
void mod1(tessera *std, int numberOfcards)
{   
    // VARIABILI GENERALI MDOALITA' 1
    int indexTable = 0;
    int choice = 0;
    int mossa1 = 1;
    int tableSize = numberOfcards;
    tessera *table = creaTable(numberOfcards); // ARRAY TAVOLO
    tessera *playerCards1 = giveTessereToPlayer(std, numberOfcards);
    //printf(" indirizzo di partenza: %p\n\n", playerCards1);

    //INTRODUZIONE GIOCO (COMPARE SOLO ALLA PRIMA PARTITA)
    printf("\nAl giocatore verranno assegnate %d tessere.\nL'obiettivo è quello di disporre le tessere sul tavolo scondo la regola:\nI numeri dei lati adiacenti tra due tessere devono essere identici.\n\n", numberOfcards);
    style();

    do
    {
        mossa(table, playerCards1, &indexTable, &numberOfcards, &choice, mossa1, tableSize);
        playerCards1 = newPlayercards(playerCards1, numberOfcards, choice);
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        //printf("indirizzo finale: %p\n\n", playerCards1);
        printTessere(table, tableSize);
        puts("");
        style();
        mossa1 = 0;
        numberOfcards -= 1;
    }
    while(numberOfcards); //per ora gioca finché hai carte

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!

    free(table);
    free(playerCards1);
}

// MOSSA MODALITA' CLASSICA
void mossa(tessera *table, tessera *playerCards1, int *indexTable, int *numberOfcards, int *choiceptr, int mossa1, int tableSize) 
{
    // VARIABILI SCELTE PLAYER 1
    bool playAgain = true;
    bool changeResp = true;
    int pushQuestion = 0;
    int risposta = 0;

    while (playAgain)
    {
        // VARIABILI SCELTE PLAYER 2
        int rotateQuestion = 0;
        *choiceptr = 0;

        //printf("%d", mossa1);

        // MOSSA 1
        // STAMPA TESSERE MANO GIOCATORE
        puts("");
        printTessere(playerCards1, *numberOfcards);
        puts("");

        // RICHIESTA TESSERA DA SCEGLIERE
        *choiceptr = chooseCard(playerCards1);
        printf("\n[%d|%d]", playerCards1[*choiceptr].num1, playerCards1[*choiceptr].num2);
        puts("\n");

        // RICHIESTA ROTAZIONE
        puts("\nVuoi ruotare la tessera selezionata?\n\n1-Si, ruotala\n2-No, lasciala così");
    
        do
        {
            printf("\nHai scelto l'opzione: ");
            scanf("%d", &rotateQuestion);
            if (rotateQuestion < 1 || rotateQuestion > 2) error("Comando non valido. Scegli tra le opzioni disponibili.\n");
        } 
        while (rotateQuestion < 1 || rotateQuestion > 2);

        if (rotateQuestion == 1) rotate(playerCards1, *choiceptr);
        printf("\n[%d|%d]\n", playerCards1[*choiceptr].num1, playerCards1[*choiceptr].num2);

        if (mossa1 == 0) // SCELTA DOVE VUOI PUSHARE
        {
            // RICHIESTA PUSH
            puts("\nDove vuoi inserire la tessera selezionata?\n\n1-A destra\n2-A sinistra");
            do
            {
            printf("\nHai scelto l'opzione: ");
            scanf("%d", &pushQuestion);
            if (pushQuestion < 1 || pushQuestion > 2) error("Comando non valido. Scegli tra le opzioni disponibili.\n");
            } 
            while (pushQuestion < 1 || pushQuestion > 2);
        }

        do
        {   
            printf("\nConfermi le scelte fatte?\n\n1: Si\n2: No\n\nHai scelto l'opzione: ");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                changeResp = false;
                playAgain = false;
                puts("");
                break;
            case 2:
                changeResp = false;
                puts("");
                style();
                break;
            default:
                error("Comando non valido. Scegli tra le opzioni disponibili.\n");
                changeResp = true;
            }
        } while (changeResp);
    }

    if (mossa1 == 1)
    {
        pushHead(table, playerCards1, *choiceptr, indexTable);
    }
    if (pushQuestion == 1)
    {
        pushHead(table, playerCards1, *choiceptr, indexTable);
    }
    if (pushQuestion == 2)
    {
        pushFooter(table, tableSize, playerCards1, *choiceptr, indexTable);
    }

}

