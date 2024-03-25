#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"
#include "check.h"


int findDim(tessera* AiCards, int tableSize) {
    int count = 0; // Inizializziamo il conteggio a 0
    int i = 0;
    while (i < tableSize)
    {
        int j = i + 1;
        count++;
        while (j < tableSize && AiCards[i].num1 == AiCards[j].num1 && AiCards[i].num2 == AiCards[j].num2) {
            j++;
        }
        i = j;
    }
    return count;
}

cardObj* createArray(tessera* AiCards, int tableSize, int size) {
    int sizeObj = findDim(AiCards, tableSize);
    cardObj* output = (cardObj*)malloc(sizeof(cardObj) * sizeObj);
    int c = 0;
    int index = 0;

    printf("La size: %d\n", size);

    while (c < size)
    {
        int frqQ = 0;
        int i = index;
        while (i < tableSize && AiCards[i].num1 == AiCards[i + 1].num1 && AiCards[i].num2 == AiCards[i + 1].num2)
        {
            frqQ++;
            i++;
        }

        output[c].card = AiCards[index];
        output[c].freq = frqQ + 1;

        index = i + 1;
        c++;
    }
    return output;
}

void swap(tessera* AiCards1, tessera* AiCards2) {
    tessera temp1 = *AiCards1;
    *AiCards1 = *AiCards2;
    *AiCards2 = temp1;
}

void sortCards(tessera* AiCards, int Size) {

    // Sort num1
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if (AiCards[j].num1 > AiCards[j + 1].num1) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }

    // Sort num2 
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if ((AiCards[j].num1 == AiCards[j + 1].num1) && (AiCards[j].num2 > AiCards[j + 1].num2)) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }
}

void modAI(tessera* alltessere, int tableSize) {

    tessera* table = creaTable(tableSize);

    tessera* AiCards = giveTessereToPlayer(alltessere, tableSize);
    printTessere(AiCards, tableSize);

    puts("\n");

    findMostFrequent(AiCards, tableSize);

    sortCards(AiCards, tableSize);
    puts(" ");
    printf("Il tavolo ordinato:\n");
    printTessere(AiCards, tableSize);

    freq* ptrFreq = getFreq();

    int sizeObj = findDim(AiCards, tableSize);
    cardObj* arrayObj = createArray(AiCards, tableSize, sizeObj);

    // for (int k = 0; k < sizeObj; k++) {
    //     printf("[%d|%d] -> %d\n", arrayObj[k].card.num1, arrayObj[k].card.num2, arrayObj[k].freq);
    // }


    free(table);
    free(AiCards);
    free(arrayObj);
}

