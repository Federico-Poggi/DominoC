#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// TIPI VARIABILI STRUCT (TIENI QUI PERCHE ALTRIMENTI FUNZIONE N3 NON VA)
typedef struct
{
    int num1;
    int num2;
} tessera;

//----------------------FUNZIONI FIRME---------------------------//
void style();
int playMode();
void error(const char *message);
tessera *stdTessere(); // FUNZIONE N3
void printTessere(tessera *a, int size);
tessera *giveTessereToPlayer(tessera *tessere, int nTessere);
void rotate(tessera *playerCards1, int i);
void mod1(tessera *std, int numberOfcards);
//---------------------------------------------------------------//

int main()
{
    // TENIAMO I PUNTATORI DELLA MEMEORIA ALLOCATA NEL MAIN
    tessera *std = stdTessere();
    srand(time(NULL));
    bool playAgain = true;
    bool changeResp = true;
    int risposta = 0;
    // printTessere(std, 6);
    const int numberOfcards = 28;


    // INTRODUZIONE
    printf("BENVENUTO IN DOMINO\n");
    while (playAgain)
    {

        style();
        int modalita = playMode();
        style();
        switch (modalita)
        {
        case 1:
            printf("Modalità: %d\n", modalita);
            style();
            mod1(std, numberOfcards);
            break;
        case 2:
            printf("Modalità: %d\n", modalita);
            break;
        case 3:
            printf("Modalità: %d\n", modalita);
            break;
        default:
            error("ERRORE\n");
        }
        // Possibilità di giocare nuovamente
        do
        {
            printf("Vuoi divertirti ancora: inserisci 0(no) o 1(si)");
            puts(" ");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                changeResp = false;
                break;
            case 0:
                changeResp = false;
                playAgain = false;
                break;
            default:
                error("Inserisci solo 0 o 1\n");
            }
        } while (changeResp);
    }

    // FREE ALL MALLOC CREATED!!!!!!!!!!
    // I Want To Be Break free
    free(std);
    return 0;
}

// FUNZIONI CREATE
void style()
{
    for (char k = 0; k <= 18; ++k)
    {
        printf("-");
    }
    puts(" ");
};
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

void error(const char *message)
{
    printf("ERRORE: %s", message);
};

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

void rotate(tessera *playerCards1, int i){
    int temp = playerCards1[i].num1;
    playerCards1[i].num1 = playerCards1[i].num2;
    playerCards1[i].num1 = temp;
}

// MODALITA' CLASSICA
void mod1(tessera *std, int numberOfcards)
{   
    printf("Tessere nella mano del giocatore 1 :");
    puts("\n");

    tessera *playerCards1 = giveTessereToPlayer(std, numberOfcards); 

    printTessere(playerCards1, numberOfcards);
    puts("\n");

    free(playerCards1);
}