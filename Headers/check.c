#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "header_domino.h"
#include "check.h"

// CONTROLLO COMPATIBILITA' TESSERE (Prende i due e)
int insertCheck(tessera *table, tessera *playercards, int dimTable, int choice)
{
    int left = table[0].num1; // Assegno l'estremo sinistro della tessera del domino a sinistra
    int right = 0;            // Variabile per il salvataggio
    for (size_t i = 0; i < dimTable; i++)
    {
        if (table[i].num2 == 0)
        {
            right = table[i - 1].num2;
            break;
        }
    }
    if ((left == playercards[choice].num2) || (right == playercards[choice].num1))
        return 1;
    else
        return 0;
}
