#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"

typedef struct
{
    tessera card;
    int freq;
} cardObj; // ogetto carta che contiene tessera e sua frequenza

int findDim(tessera* AiCards, int tableSize) {
    int count = 1; // prima tessera non ha doppioni
    for (int i = 1; i < tableSize; i++) {
        count++;
        for (int j = i - 1; j >= 0; j--) {
            if ((AiCards[i].num1 == AiCards[j].num1) && (AiCards[i].num2 == AiCards[j].num2)) {
                count--;
            }
        }
    }
    return count;
}

/*
cardObj *createArray (tessera *AiCards, int tableSize) {
    int sizeObj = findDim (AiCards, tableSize);
    cardObj *output = (cardObj *)malloc(sizeof(cardObj) * sizeObj);



    roba simile a prima du find dim ma con l'array obj

    output[0].card
    for (int i = 1; i < tableSize; i++) {
        for (int j = 0; j < tableSize; j++)  {

        }
    }





    return output;
}
*/

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
    // printTessere(AiCards, tableSize);

    freq* ptrFreq = getFreq();

    for (size_t i = 0; i < 6; i++)
    {
        printf("{%d|%d}", ptrFreq[i].num, ptrFreq[i].frequency);
    }


    //int sizeObj = findDim (AiCards, tableSize); 
    //cardObj *arrayObj = createArray (AiCards, tableSize);




    free(table);
    free(AiCards);
    //free(arrayObj);
}

