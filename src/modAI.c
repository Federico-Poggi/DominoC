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

tessera rotateAI(tessera playerCards1)
{
    int temp = playerCards1.num1; // variabile temporanea salvata per lo swap
    playerCards1.num1 = playerCards1.num2;
    playerCards1.num2 = temp;
    return playerCards1;
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
//* Funzione per decrementare le frequenza man mano che si inseriscono le carte
void decrement(int num) {
    freq* frequencies = getFreq();
    for (size_t i = 0; i < MAX_VAL_TESSERA; i++)
    {
        if (frequencies[i].num == num)
        {
            frequencies[i].frequency--;
        }
    }
}
int obtainCard(cardObj* arrayObj, int sizeObj) {
    int max = arrayObj[0].freq;
    int totalPoint = 0;
    int tempPoint = 0;
    int index1 = 0;
    for (int i = 1; i < sizeObj; i++) {
        tempPoint = arrayObj[i].card.num1 + arrayObj[i].card.num2;
        if (arrayObj[i].freq >= max && totalPoint < tempPoint) {
            max = arrayObj[i].freq;
            totalPoint = tempPoint;
            index1 = i;
        }
    }
    printf("%d freq %d", max, index1);
    return index1;
}

void pushHeadAI(tessera* table, cardObj* arrayObj, int indexCard, int* pointer)
{
    table[*pointer] = arrayObj[indexCard].card;
    *pointer += 1; // VARIFICA CHE QUANDO PUNTA ALL' ELEMENTO 29 NON SIA POSSIBILE INSERIRE O ESSERCI LATRO (OUT OF ARRAY)
}

void insertdx(cardObj* arrayObj, int indexCard, tessera* table, int* pointer) {
    tessera card = arrayObj[indexCard].card;
    for (int i = 1; i <= arrayObj[indexCard].freq; i++) {
        if ((i % 2) == 0) {
            tessera cardRotated = rotateAI(card);
            printf("[%d|%d]", cardRotated.num1, cardRotated.num2);
            pushHeadAI(table, arrayObj, indexCard, pointer);
        }
        else {
            pushHeadAI(table, arrayObj, indexCard, pointer);
        }
    }
}

void modAI(tessera* alltessere, int tableSize) {

    // 1: setting IA
    // Creazione tavolo e tessere
    tessera* table = creaTable(tableSize);
    int indexTableAI = 0;
    tessera* AiCards = giveTessereToPlayer(alltessere, tableSize);
    printTessere(AiCards, tableSize);
    puts("\n");
    sortCards(AiCards, tableSize);
    // Ordinmanto e Registro frequenze tessere
    int most = findMostFrequent(AiCards, tableSize);

    printf("\n Il numero più frequente è : %d\n", most);

    freq* ptrFreq = getFreq();

    for (size_t i = 0; i < MAX_VAL_TESSERA; i++)
    {
        printf("\nN: %d,  F:%d\n", ptrFreq[i].num, ptrFreq[i].frequency);
    }

    printTessere(AiCards, tableSize);

    int sizeObj = findDim(AiCards, tableSize);
    cardObj* arrayObj = createArray(AiCards, tableSize, sizeObj);

    //printTessere(AiCards, tableSize);

    for (int k = 0; k < sizeObj; k++) {
        printf("[%d|%d] -> %d\n", arrayObj[k].card.num1, arrayObj[k].card.num2, arrayObj[k].freq);
    }

    // 2: partita IA
    //trova la tessera più frequente

    int indexCard = obtainCard(arrayObj, sizeObj);
    insertdx(arrayObj, indexCard, table, &indexTableAI); //pushhead

    puts("\n\n");

    printTessere(table, tableSize);

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
    free(AiCards);
    free(arrayObj);

    // FINE
}

