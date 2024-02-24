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
        printf("La tessere [%d|%d] può essere inserita\n", playercards[*choice].num1, playercards[*choice].num2);
        puts(" ");
        return true;
    }
    else
    {

        printf("La tessere [%d|%d] non può essere inserita: Inserire una tessera valida \n", playercards[*choice].num1, playercards[*choice].num2);
        puts(" ");
        return false;
    };
}