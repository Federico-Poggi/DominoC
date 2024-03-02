#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"

// FUNZIONE STILE GRAFICA
void style()
{
    for (char k = 0; k <= 90; ++k)
    {
        printf("\033[1;35m-\033[0m");
    }
    puts(" ");
};

// STAMPA ERRORE
void error(const char *message)
{
    printf("\033[1;31mERRORE: %s\033[0m", message);
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

// STAMPA TAVOLO E TESSERE
void printTessere(tessera *a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if ((a[i].num1 != 0) && (a[i].num2 != 0))
        {
            if (i == (size / 2))
                puts("");
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
// SCELTA TESSERA MANO GIOCATORE (NO AI)
int chooseCard(tessera *playercards, int *numberOfcards)
{
    int indice = 0;
    bool verifica = true;
    // Da aggiungere una variabile che tiene il conto delle carte in mano del giocatore; quindi a ogni ciclo corretto diminuire questo numero e quindi stampare "Scegliere una tessera da 1 a n-1"
    while (verifica)
    {
        printf("Quale tessera vuoi giocare?\nScegliere un numero da 1 a %d: ",
               *numberOfcards);
        scanf("%d", &indice);
        if (indice <= *numberOfcards && indice >= 1)
            verifica = false;
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
    } // errore allocazione memoria

    // INIZIALIZZO NEW
    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != choice)
        {
            new[j++] = playerCards1[i];
        }
    }

    // SALVO INDIRIZZO VECCHIA MALLOC PER LIBERARLA
    tessera *vecchioArray = playerCards1; // free contiene indirizzo vecchio array;

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