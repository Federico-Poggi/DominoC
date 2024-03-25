#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"

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

int findDim(tessera* AiCards, int tableSize) {
    
}

cardObj *createArray (tessera *AiCards, int tableSize, int size) {
    
}

void modAI(tessera* alltessere, int tableSize) {

    // 1: setting IA

    // Creazione tavolo e tessere
    tessera* table = creaTable(tableSize);
    tessera* AiCards = giveTessereToPlayer(alltessere, tableSize);
    printTessere(AiCards, tableSize);
    puts("\n");

    // Ordinmanto e Registro frequenze tessere
    findMostFrequent(AiCards, tableSize);
    freq* ptrFreq = getFreq();
    sortCards(AiCards, tableSize); 
    printTessere(AiCards, tableSize);
    int sizeObj = findDim (AiCards, tableSize);
    cardObj *arrayObj = createArray (AiCards, tableSize, sizeObj);

    //printTessere(AiCards, tableSize);

    for (int k = 0; k < sizeObj; k++) {
        printf("[%d|%d] -> %d\n", arrayObj[k].card.num1, arrayObj[k].card.num2, arrayObj[k].freq);
    }

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
    free(AiCards);
    free(arrayObj);

    // FINE
}

