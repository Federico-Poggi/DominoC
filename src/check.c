#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"

bool insertCheck(tessera *table, tessera *playercards, int *indexTable, int *choice)
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

bool checkInsertable(tessera *table, tessera *playercards, int *indexTable, int *choice, int dxOrSx, int mossa1)
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