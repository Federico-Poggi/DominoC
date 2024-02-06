#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
void mod1();
//---------------------------------------------------------------//

int main()
{
    // TENIAMO I PUNTATORI DELLA MEMEORIA ALLOCATA NEL MAIN
    tessera *std = stdTessere();
    // printTessere(std, 6);

    // INTRODUZIONE
    printf("BENVENUTO IN DOMINO\n");

    style();
    int modalita = playMode();
    style();
    switch (modalita)
    {
    case 1:
        printf("Modalità: %d\n", modalita);
        style();
        mod1(std, 10);
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

    // FREE ALL MALLOC CREATED!!!!!!!!!!
    // I Want To Be Break free
    free(std);
    return 0;
};

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
    srand(time(NULL));
    int randNumberForCycleTheCards;
    for (int i = 0; i < nTessere; ++i)
    {
        randNumberForCycleTheCards = rand() % 21;
        // printf("[%d|%d]", tessere[randNumberForCycleTheCards].num1, tessere[randNumberForCycleTheCards].num2);
        palyerCards[i].num1 = tessere[randNumberForCycleTheCards].num1;
        palyerCards[i].num2 = tessere[randNumberForCycleTheCards].num2;
    }
    return palyerCards;
}
// MODALITA' CLASSICA
void mod1(tessera *std, int numberOfTesser)
{
    printf("Carte nella tua mano:");
    puts("\n");
    tessera *playerCards = giveTessereToPlayer(std, numberOfTesser);
    for (int i = 0; i < numberOfTesser; i++)
    {
        printf("[%d|%d] ", playerCards[i].num1, playerCards[i].num2);
    }
    puts("\n");
}