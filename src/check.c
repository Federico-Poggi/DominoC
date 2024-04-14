
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"
/**
 * @brief **Check if a tile can be inserted into table**
 *
 *
 *  This function checks whether the tile chosen by the player can be placed on the game board.
 *  It does this by comparing the values of the left and right ends of the board with the values of the ends
 *  of the chosen tile.
 *
 * @param table *Game board array*
 * @param playercards *Player's hand*
 * @param indexTable *Last inserted tile pointer in the game board*
 * @param choice *Pointer to the chosen tile from the player*
 * @return **TRUE** *If the tile can be inserted into the game board*
 * @return **FALSE** *If the tile can't be inserted into the game board*
 *
 * \code
 *  bool insertCheck(tessera* table, tessera* playercards, int* indexTable, int* choice)
{

    int left = table[0].num1;                // Most left number
    int right = table[*indexTable - 1].num2; // Most right number
    if ((left == playercards[*choice].num2) || (left == playercards[*choice].num1) || (right == playercards[*choice].num1) || (right == playercards[*choice].num2))
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        return true;
    }
    else if (left == 0 && right == 0)
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        //printf("Prima mossa");
        return true;
    }
    else
    {
        printf("\033[1;31mLa tessere [%d|%d] non può essere inserita: inserire una tessera valida\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        return false;
    };
 * \endcode
 */
bool insertCheck(tessera* table, tessera* playercards, int* indexTable, int* choice)
{

    int left = table[0].num1;                // Assegno l'estremo sinistro della  tessera del domino a sinistra
    int right = table[*indexTable - 1].num2; // Variabile per il salvataggio
    if ((left == playercards[*choice].num2) || (left == playercards[*choice].num1) || (right == playercards[*choice].num1) || (right == playercards[*choice].num2))
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        return true;
    }
    else if (left == 0 && right == 0)
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        //printf("Prima mossa");
        return true;
    }
    else
    {
        printf("\033[1;31mLa tessere [%d|%d] non può essere inserita: inserire una tessera valida\n\033[0m", playercards[*choice].num1, playercards[*choice].num2);
        return false;
    };
}

bool checkInsertable(tessera* table, tessera* playercards, int* indexTable, int* choice, int dxOrSx, int mossa1)
{
    // Estremo più a destra
    int left = table[0].num1;
    // Estrmo più a sinistra
    int right = table[*indexTable - 1].num2;

    bool insertable = false;
    // Tessera scelta dal giocatore ruotata o no;
    tessera playerChoice = playercards[*choice];

    if (mossa1 == 1)
    {
        insertable = true;
        return insertable;
    }

    switch (dxOrSx)
    {
    case 1:
        // DESTRA
        //  Valore estremo sinistro della tessera scelta
        int value1 = playerChoice.num1;
        insertable = (value1 == right) ? true : false;
        if (insertable == false) {
            puts("");
            error("La tessera deve essere inserita in altra maniera");
            puts("");
        }
        break;

    case 2:
        // SINISTRA
        // Valore estremo destra della tessera scelta
        int value2 = playerChoice.num2;
        insertable = (value2 == left) ? true : false;
        if (insertable == false) {
            puts("");
            error("La tessera deve essere inserita in altra maniera");
            puts("");
        }
        break;
    default:
        error("La tessera deve essere inserita in altra maniera");
    }
    return insertable;
}

/**
 * @brief **Check if in the Player hand there are one or more tiles that can be inserted**
 *
 * @param table *Game Board*
 * @param playCards *Player hand*
 * @param indexTable *Index of the last tile inserted*
 * @param numberOfCards
 * @param playerMode
 * @return **TRUE** *If there is at least one tile that can be inserted*
 * @return **FALSE** *If there's no more tiles insertable*
 *
 * \code{c}
 * bool canGoNext(tessera* table, tessera* playCards, int* indexTable, int numberOfCards, bool playerMode)
{
    int mostLeft = table[0].num1;
    int mostRight = table[*indexTable - 1].num2;

    for (unsigned int j = 0; j < numberOfCards; j++)
    {
        if ((mostLeft == playCards[j].num2) || (mostLeft == playCards[j].num1) || (mostRight == playCards[j].num1) || (mostRight == playCards[j].num2))
        {
            if (playerMode == true) {
                // Can follow
                printf("\033[1;32m\nSi puo proseguire: inserire una tessera valida \n\033[0m");
            }
            return true;
        }
    }
    printf("\033[1;31m\nMosse possibili terminate\n\033[0m");
    return false;
}
 * \endcode
 */
bool canGoNext(tessera* table, tessera* playCards, int* indexTable, int numberOfCards, bool playerMode)
{
    int mostLeft = table[0].num1;
    int mostRight = table[*indexTable - 1].num2;

    for (unsigned int j = 0; j < numberOfCards; j++)
    {
        if ((mostLeft == playCards[j].num2) || (mostLeft == playCards[j].num1) || (mostRight == playCards[j].num1) || (mostRight == playCards[j].num2))
        {
            if (playerMode == true) {
                // E' possibile proseguire il gioco
                printf("\033[1;32m\nSi puo proseguire: inserire una tessera valida \n\033[0m");
            }
            return true;
        }
    }
    printf("\033[1;31m\nMosse possibili terminate\n\033[0m");
    return false;
}
