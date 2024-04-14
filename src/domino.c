#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"

const MAX_VAL_TESSERA = 6;

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
/**
 * @brief **Print error**
 *
 *
 * @param message *Error message*
 *
 *\code{c}
 * void error(const char* message)
{
    printf("\033[1;31mERRORE: %s\033[0m", message);
};

 *\endcode
 */
void error(const char* message)
{
    printf("\033[1;31mERRORE: %s\033[0m", message);
};

// GENERA TESSERE STANDARD
/**
 * @brief **Generate the standard domino's tiles**
 *
 * \code{c}
 * tessera* stdTessere()
 *{
 *   const int lunghezza = 21;
 *   const int maxValue = 6;
 *   tessera* std = (tessera*)malloc(sizeof(tessera) * lunghezza);
 *   if (std == NULL)
 *   {
 *
 *       error("Errore di allocazione di memoria");
 *       exit(EXIT_FAILURE);
 *   }
 *   int i = 0;
 *
 *   for (int n1 = 1; n1 <= maxValue; ++n1)
 *   {
 *
 *       for (int n2 = n1; n2 <= maxValue; ++n2)
 *       {
 *           std[i].num1 = n1;
 *           std[i++].num2 = n2;
 *       }
 *   }
 *   return std;
 *  }
 * \endcode
 *
 * @return **tessera** *The generated array of tile with value from 1 to 6. Ex: [1|5],[6|3]*
 */
tessera* stdTessere()
{
    const int lunghezza = 21;
    const int maxValue = 6;
    // STD NOME UNIVOCO PER NON FARE CONFUSIONE
    // EQUIVALENTE CODICE ---> tessera std[21];
    tessera* std = (tessera*)malloc(sizeof(tessera) * lunghezza);
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
/**
 * @brief **Generate the game board with n. tiles**
 *
 * @param numberOfTesser *Number of tiles to generate*
 *
 * \code{c}
 *  tessera* creaTable(int numberOfTesser)
 *   {
 *  tessera* table = (tessera*)malloc(sizeof(tessera) * numberOfTesser);
 *   for (int i = 0; i < numberOfTesser; i++) {
 *       table[i].num1 = 0;
 *       table[i].num2 = 0;
 *   }
 *   return table;
 *   }
 * \endcode
 *
 * @return tessera*
 */
tessera* creaTable(int numberOfTesser)
{
    tessera* table = (tessera*)malloc(sizeof(tessera) * numberOfTesser);
    for (int i = 0; i < numberOfTesser; i++) {
        table[i].num1 = 0;
        table[i].num2 = 0;
    }
    return table;
}

// STAMPA TAVOLO E TESSERE
/**
 * @brief **Generate the game board with n. tiles**
 *
 * @param a *array of cards to be printed*
 *
 *
 * \code{c}
 * void printTessere(tessera* a, int size)
 * {
 *   for (int i = 0; i < size; ++i)
 *   {
 *       if ((a[i].num1 != 0) && (a[i].num2 != 0))
 *       {
 *            if (((i % 15) == 0) && (i != 0)) {
 *              puts("");
 *           }
 *           printf("[%d|%d] ", a[i].num1, a[i].num2);
 *       }
 *   }
 *   puts("");
 * }
 * \endcode
 *
 * @return tessera*
 */
void printTessere(tessera* a, int size)
{
    for (int i = 0; i < size; ++i)
    {
        if ((a[i].num1 != 0) && (a[i].num2 != 0))
        {
            if (((i % 15) == 0) && (i != 0)) {
                puts("");
            }
            printf("[%d|%d] ", a[i].num1, a[i].num2);
        }
    }
    puts("");
}
// FUNZIONE PER DISTRIBUIRE LE TESSERE IN BASE AL NUMERO PASSATO DI TESSERE VOLUTE IN MANO DEL GIOCATORE TUTTO CASUALE!!!!
/**
 * @brief **This will give n. tiles to player**
 *
 * @param tessere *This is the tiles standard array*
 * @param nTessere *Number of tiles to give to player*
 *
 * \code
 * tessera* giveTessereToPlayer(tessera* tessere, int nTessere)
 *   {
 *   tessera* palyerCards = (tessera*)malloc(sizeof(tessera) * nTessere);

 *   int randNumberForCycleTheCards;
 *   for (int i = 0; i < nTessere; ++i)
 *   {
 *       randNumberForCycleTheCards = rand() % 21;
 *       palyerCards[i].num1 = tessere[randNumberForCycleTheCards].num1;
 *       palyerCards[i].num2 = tessere[randNumberForCycleTheCards].num2;
 *   }

 *   return palyerCards;
 * }
 * \endcode
 *
 * @return tessera* *Will return the player hand*
 */
tessera* giveTessereToPlayer(tessera* tessere, int nTessere)
{
    tessera* palyerCards = (tessera*)malloc(sizeof(tessera) * nTessere);

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
/**
 * @brief  **Player choose**
 *
 * @param playercards *Player hand*
 * @param numberOfcards *Number of card into player hands*
 *
 * \code
 *   int chooseCard(tessera* playercards, int* numberOfcards)
{
    int indice = 0;
    bool verifica = true;

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
 *
 * \endcode
 *
 * @return **int** *This is the index of tile inside player hand*
 */
int chooseCard(tessera* playercards, int* numberOfcards)
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
/**
 * @brief **Rotate the tile when we need**
 * *Ex:* [5|1]--> [1|5]
 * @param playerCards1 *Player hands to chose the tile to rotate*
 * @param i *Index of the tile inside palyer hand*
 *
 *  \code{c}
 *  void rotate(tessera* playerCards1, int i)
{
    int temp = playerCards1[i].num1; // variabile temporanea salvata per lo swap
    playerCards1[i].num1 = playerCards1[i].num2;
    playerCards1[i].num2 = temp;
}
 * \endcode
 *
 */
void rotate(tessera* playerCards1, int i)
{
    int temp = playerCards1[i].num1; // variabile temporanea salvata per lo swap
    playerCards1[i].num1 = playerCards1[i].num2;
    playerCards1[i].num2 = temp;
}

// PUSH HEAD TESSERA
/**
 * @brief **Insert the tile at the end of game board**
 *
 * @param table *Game board*
 * @param playerCards1 *Player hand*
 * @param choice *index of chosen tile*
 * @param pointer *Index last tile inserted into table*
 *
 * \code{c}
 *  void pushHead(tessera* table, tessera* playerCards1, int choice, int* pointer)
{
    table[*pointer] = playerCards1[choice];
    *pointer += 1; // VARIFICA CHE QUANDO PUNTA ALL' ELEMENTO 29 NON SIA POSSIBILE INSERIRE O ESSERCI LATRO (OUT OF ARRAY)
}

 * \endcode
 */
void pushHead(tessera* table, tessera* playerCards1, int choice, int* pointer)
{
    table[*pointer] = playerCards1[choice];
    *pointer += 1; // VARIFICA CHE QUANDO PUNTA ALL' ELEMENTO 29 NON SIA POSSIBILE INSERIRE O ESSERCI LATRO (OUT OF ARRAY)
}

// PUSH FOOTER TESSERA 
/**
 * @brief **Insert the tile at start of game board**
 *
 * @param table *Game board*
 * @param playerCards1 *Player hand*
 * @param size *Size of game board*
 * @param choice *index of chosen tile*
 * @param pointer *Index last tile inserted into table*
 *
 * \code{c}
void pushFooter(tessera* table, int size, tessera* playerCards1, int choice, int* pointer)
{
    for (size_t i = size - 1; i > 0; i--)
    {
        table[i] = table[i - 1];
    }
    table[0] = playerCards1[choice];
    *pointer += 1;
}
 * \endcode
 */
void pushFooter(tessera* table, int size, tessera* playerCards1, int choice, int* pointer)
{
    for (size_t i = size - 1; i > 0; i--)
    {
        table[i] = table[i - 1];
    }
    table[0] = playerCards1[choice];
    *pointer += 1;
}

// RIDUZIONE ARRAY
/**
 * @brief **Remove tiles from Player hands when a tile is inserted**
 *
 * @param playerCards1 *Player hand*
 * @param size *Current player hand size *
 * @param choice *Index of chosen tile*
 *
 * \code{c}
 *
 *tessera* newPlayercards(tessera* playerCards1, int size, int choice)
{
    tessera* new = (tessera*)malloc(sizeof(tessera) * (size - 1)); // RIDUCI FUORI DALLA FUNZIONE LA DIMENSIONE DELLA MANO
    if (new == NULL)
    {
        error("Errore di allocazione di memoria");
        exit(EXIT_FAILURE);
    }

    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != choice)
        {
            new[j++] = playerCards1[i];
        }
    }

    tessera* vecchioArray = playerCards1;





    free(vecchioArray);

    return new;
}
 *
 * \endcode
 *
 * @return tessera* *New resized player hand*
 */
tessera* newPlayercards(tessera* playerCards1, int size, int choice)
{
    // CREAZIONE NUOVA MEMEORIA
    tessera* new = (tessera*)malloc(sizeof(tessera) * (size - 1)); // RIDUCI FUORI DALLA FUNZIONE LA DIMENSIONE DELLA MANO
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
    tessera* vecchioArray = playerCards1; // free contiene indirizzo vecchio array;




    // FREE MALLOC INDIRIZZO VECCHIO 0x7f017e8973e0
    free(vecchioArray);

    return new; // NUOVO INDIRIZZO CONTENTE NUOVA MALLOC 0x5598feb00d50
}

// PUNTEGGI FINALI
/**
 * @brief **Print of final point**
 *
 * @param table *Game board*
 * @param sizeTab *Game board size*
 *
 * \code
 * int endPoints(tessera* table, int sizeTab) {
    int sumPoint = 0;
    for (int k = 0; k < sizeTab; k++) {
        if (table[k].num1 == 0) {
            continue;
        }
        sumPoint += table[k].num1 + table[k].num2;
        //printf("sum = %d", sumPoint);
    }
    return sumPoint;
}
 * \endcode
 *
 * @return int
 */
int endPoints(tessera* table, int sizeTab) {
    int sumPoint = 0;
    for (int k = 0; k < sizeTab; k++) {
        if (table[k].num1 == 0) {
            continue;
        }
        sumPoint += table[k].num1 + table[k].num2;
        //printf("sum = %d", sumPoint);
    }
    return sumPoint;
}


