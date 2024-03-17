#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"
/**
 * @brief Controlla se è possibile inserire una tessera sulla tavola di gioco.
 *
 * Questa funzione controlla se la tessera scelta dal giocatore può essere inserita sulla tavola di gioco.
 * Per farlo, confronta i valori delle estremità sinistra e destra della tavola con i valori delle estremità
 * della tessera scelta.
 *
 * @param table Array rappresentante la tavola di gioco.
 * @param playercards Array delle tessere del giocatore.
 * @param indexTable Puntatore all'indice dell'ultima tessera inserita sulla tavola di gioco.
 * @param choice Puntatore all'indice della tessera scelta dal giocatore.
 * @return true Se la tessera può essere inserita sulla tavola di gioco.
 * @return false Se la tessera non può essere inserita sulla tavola di gioco.
 */

bool insertCheck(tessera* table, tessera* playercards, int* indexTable, int* choice)
{

    int left = table[0].num1;                // Assegno l'estremo sinistro della  tessera del domino a sinistra
    int right = table[*indexTable - 1].num2; // Variabile per il salvataggio
    if ((left == playercards[*choice].num2) || (left == playercards[*choice].num1) || (right == playercards[*choice].num1) || (right == playercards[*choice].num2))
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n \033[0m\n", playercards[*choice].num1, playercards[*choice].num2);
        puts(" ");
        return true;
    }
    else if (left == 0 && right == 0)
    {
        printf("\033[1;32mLa tessere [%d|%d] può essere inserita\n \033[0m\n", playercards[*choice].num1, playercards[*choice].num2);
        puts(" ");
        printf("Prima mossa");
        return true;
    }
    else
    {
        printf("\033[1;31m La tessere [%d|%d] non può essere inserita: inserire una tessera valida \n \033[0m\n", playercards[*choice].num1, playercards[*choice].num2);
        puts(" ");
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
        break;

    case 2:
        // SINISTRA
        // Valore estremo destra della tessera scelta
        int value2 = playerChoice.num2;
        insertable = (value2 == left) ? true : false;
        break;
    default:
        error("La tessera deve essere inserita in altra maniera");
    }
    return insertable;
}

bool canGoNext(tessera* table, tessera* playCards, int* indexTable, int numberOfCards)
{
    int mostLeft = table[0].num1;
    int mostRight = table[*indexTable - 1].num2;

    for (unsigned int j = 0; j < numberOfCards; j++)
    {
        if ((mostLeft == playCards[j].num2) || (mostLeft == playCards[j].num1) || (mostRight == playCards[j].num1) || (mostRight == playCards[j].num2))
        {
            // E' possibile proseguire il gioco
            printf("\033[1;32m Si puo proseguire: inserire una tessera valida \n \033[0m\n");
            return true;
        }
    }
    printf("\033[1;31m Mosse possibili terminate \n \033[0m\n");
    return false;
}

int findMostFrequent(tessera* table, int tableSize) {
    int most_frequent = 0;
    int frequenza = 0;

    for (size_t i = 0; i < tableSize; i++)
    {
        tessera current_value = table[i];

        int repetition_num1 = 0;
        int repetition_num2 = 0;

        int tessera_num1 = current_value.num1;
        int tessera_num2 = current_value.num2;

        for (size_t k = i; k < tableSize; k++)
        {
            tessera thisTessera = table[k];
            int numberOfThis_1 = thisTessera.num1;
            int numberOfThis_2 = thisTessera.num2;

            if ((numberOfThis_1 == tessera_num1) || (numberOfThis_1 == tessera_num2)) {
                repetition_num1++;
                printf("*\n");
            }

            if (((numberOfThis_2 == tessera_num1) || (numberOfThis_2 == tessera_num2)))
            {
                repetition_num2++;
                printf("X\n");
            }
        }

        if (repetition_num1 > repetition_num2) {
            if (repetition_num1 > frequenza) {
                frequenza = repetition_num1;
                most_frequent = current_value.num1;
            }
        }
        else {
            if (repetition_num2 > frequenza) {
                frequenza = repetition_num2;
                most_frequent = current_value.num2;
            }
        }


    }
    printf("Ferquenza  %d e numero_tessera %d", frequenza, most_frequent);
    return most_frequent;
}

