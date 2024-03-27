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
    // printf("%d freq %d", max, index1);
    return index1;
}

//* Ritorna la tessera nell'arrayObj 
tessera getTessera(cardObj* arrObj, int indexObj) {
    return arrObj[indexObj].card;
}

void pushHeadAI(tessera* table, tessera t, int* pointer)
{
    table[*pointer] = t;
    *pointer += 1;
}

//* Funzione per rimuove la tessera inserita
void removeTessera(tessera toRemove, tessera* AiCards, int* AiCardsSize) {
    bool found = false;
    int indexToDelete = -1;
    // printf("[%d|%d]", toRemove.num1, toRemove.num2);
    for (size_t i = 0; i < *AiCardsSize; i++)
    {
        if ((AiCards[i].num1 == toRemove.num1) && (AiCards[i].num2 == toRemove.num2)) {
            found = true;
            indexToDelete = i;
            break;
        }
    }
    // printf("Index to delate: %d\n", indexToDelete);

    if (!found) {
        printf("\nTessera non trovata");
        return;
    }

    for (size_t k = indexToDelete; k < *AiCardsSize; k++) {
        AiCards[k] = AiCards[k + 1];
    }

    (*AiCardsSize)--;
}

//* Inserimento prima tessera al momento;
void insert(tessera* AiCards, int tabSize, tessera mostFreq, tessera* table, int* ptrTable, int* AICardSize, int freqTessera) {
    int count = 0;
    for (size_t i = 0; i < tabSize; i++)
    {
        if (mostFreq.num1 == AiCards[i].num1 && mostFreq.num2 == AiCards[i].num2)
        {
            count++;
            if (count % 2 == 0) {
                tessera tes = rotateAI(AiCards[i]);
                printf("Tessera ruotata: [%d|%d]", tes.num1, tes.num2);
                pushHeadAI(table, tes, ptrTable);

            }
            else {
                pushHeadAI(table, AiCards[i], ptrTable);
            }
        }


    }
    for (size_t i = 0; i < freqTessera; i++)
    {
        removeTessera(mostFreq, AiCards, AICardSize);
    }

}

void modAI(tessera* alltessere, int tableSize) {

    // 1: setting IA
    // Creazione tavolo e tessere
    tessera* table = creaTable(tableSize);
    int indexTableAI = 0;

    //* Carte in mano all'ia
    tessera* AiCards = giveTessereToPlayer(alltessere, tableSize);
    int AicardSize = tableSize;
    int* ptrAiCardSize = &AicardSize;

    printTessere(AiCards, tableSize);
    puts("\n");
    sortCards(AiCards, tableSize);
    // Ordinmanto e Registro frequenze tessere
    int most = findMostFrequent(AiCards, tableSize);

    // printf("\n Il numero più frequente è : %d\n", most);

    freq* ptrFreq = getFreq();

    // for (size_t i = 0; i < MAX_VAL_TESSERA; i++)
    // {
    //     printf("\nN: %d,  F:%d\n", ptrFreq[i].num, ptrFreq[i].frequency);
    // }

    printTessere(AiCards, tableSize);

    int sizeObj = findDim(AiCards, tableSize);
    cardObj* arrayObj = createArray(AiCards, tableSize, sizeObj);

    //printTessere(AiCards, tableSize);

    // for (int k = 0; k < sizeObj; k++) {
    //     printf("[%d|%d] -> %d\n", arrayObj[k].card.num1, arrayObj[k].card.num2, arrayObj[k].freq);
    // }

    // 2: partita IA
    //trova la tessera più frequente

    int indexCard = obtainCard(arrayObj, sizeObj);
    int freqIndexCard = arrayObj[indexCard].freq;
    tessera mostFreq = getTessera(arrayObj, indexCard);

    insert(AiCards, tableSize, mostFreq, table, &indexTableAI, ptrAiCardSize, freqIndexCard);

    // insertdx(arrayObj, indexCard, table, &indexTableAI, AiCards, tableSize); //pushhead

    puts("\n\n");

    printTessere(table, tableSize);
    // for (size_t i = 0; i < freqIndexCard; i++)
    // {
    //     removeTessera(mostFreq, AiCards, ptrAiCardSize);
    // }

    printTessere(AiCards, tableSize);
    printf("%d", *ptrAiCardSize);
    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
    free(AiCards);
    free(arrayObj);

    // FINE
}
