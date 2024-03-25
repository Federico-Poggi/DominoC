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

// Funzioni controllo Interattiva

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


// Funzioni controllo IA

freq totalFreq[];

freq* getFreq() {
    return totalFreq;
}

// * Table contiene le tessere del tavolo
//* funzioni per riordinare un array temporaneo 
void sortMerge(tessera tempTable[], int left, int right) {

    if (left < right) {
        int middle = (left + right) / 2;
        sortMerge(tempTable, left, middle);
        sortMerge(tempTable, middle + 1, right);
        merge(tempTable, left, right, middle);
    }

}

void merge(tessera tempTable[], int left, int right, int middle) {
    int i;
    int j;
    int k;

    int sizeSub1 = middle - left + 1;
    int sizeSub2 = right - middle;
    //* creo due sottoarray con gli elemernti di destra e sinistra
    tessera sub1[sizeSub1];
    tessera sub2[sizeSub2];

    //* riempio gli array con gli elementi
    for (size_t i = 0; i < sizeSub1; i++)
    {
        sub1[i] = tempTable[left + i];
    }

    for (size_t j = 0; j < sizeSub2; j++)
    {
        sub2[j] = tempTable[middle + 1 + j];
    }

    //* REinizializzo l'indice del primo sub Array
    i = 0;
    //* REinizializzo l'indice del secondo sub Array
    j = 0;

    //*L'indice dell'array unito
    k = left;

    while (i < sizeSub1 && j < sizeSub2) {
        if (sub1[i].num1 >= sub2[j].num1) {
            tempTable[k] = sub1[i];
            i++;
        }
        else {
            tempTable[k] = sub2[j];
            j++;
        }
        k++;
    }

    //* copiare le tessere rimanenti se prersenti dentro sub1 o sub2

    while (i < sizeSub1)
    {
        tempTable[k] = sub1[i];
        i++;
        k++;
    }
    while (j < sizeSub2)
    {
        tempTable[k] = sub2[j];
        j++;
        k++;
    }

}

void updateFreq(freq* freqTot, int num, int frequency) {
    for (size_t i = 0; i < 6; i++)
    {
        if (freqTot[i].num == num && freqTot[i].frequency <= frequency) {
            freqTot[i].frequency = frequency;
            break;
        }
    }

}

void sumFreq(freq* freqTot1, freq* freqTot2) {
    for (size_t i = 0; i < 6; i++)
    {
        freqTot1[i].frequency += freqTot2[i].frequency;
    }
}



void printFreq(freq* freqTot) {
    for (size_t i = 0; i < 6; i++)
    {
        printf("Numero: %d\n", freqTot[i].num);
        printf("frequ: %d\n", freqTot[i].frequency);
    }
}

int findMostFrequent(tessera* table, int tableSize) {
    tessera* tempTable = malloc(tableSize * sizeof(tessera));
    int mostFreq;
    if (tempTable == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(tempTable, table, tableSize * sizeof(table));

    int leftIndex = 0;
    int rightIndex = tableSize - 1;

    sortMerge(tempTable, leftIndex, rightIndex);

    /*
    for (size_t i = 0; i < tableSize; i++)
    {
        printf("[%d|%d]", tempTable[i].num1, tempTable[i].num2);
    }
    puts(" ");
    */

    //*Array con frequenze;
    //** Frequenze num1
    freq freq_tot[6] = {
           {1,0},
           {2,0},
           {3,0},
           {4,0},
           {5,0},
           {6,0}
    };

    //**frequenze num2
    freq freq_tot_num2[6] = {
            {1,0},
            {2,0},
            {3,0},
            {4,0},
            {5,0},
            {6,0}
    };

    freq* ptr = freq_tot;
    freq* ptr2 = freq_tot_num2;

    //* frequNum1
    for (size_t i = 0; i < tableSize; i++)
    {
        int num1 = tempTable[i].num1;
        int counter = 1;
        int k = i + 1;
        while (k < tableSize && tempTable[k].num1 == num1)
        {
            counter++;
            k++;
        }
        updateFreq(ptr, num1, counter);
    }

    for (size_t i = 0; i < tableSize; i++)
    {
        rotate(tempTable, i);
    }

    sortMerge(tempTable, leftIndex, rightIndex);

    //*frequenze num1(num2);
    for (size_t i = 0; i < tableSize; i++)
    {
        int num1 = tempTable[i].num1;
        int counter2 = 1;
        int k = i + 1;
        while (k < tableSize && tempTable[k].num1 == num1)
        {
            counter2++;
            k++;
        }
        updateFreq(ptr2, num1, counter2);
    }

    sumFreq(ptr, ptr2);
    // printFreq(ptr);

    for (size_t i = 0; i < 6; i++)
    {
        if (mostFreq < ptr[i].frequency) {
            mostFreq = ptr[i].num;
        }
    }

    for (size_t i = 0; i < 6; i++)
    {
        totalFreq[i] = freq_tot[i];
    }


    //printf("Il numero più frequente è: %d", mostFreq);

    free(tempTable);
    return mostFreq;
}

