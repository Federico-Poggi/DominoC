#include "ai.h"
#include <stdio.h>
#include <stdbool.h>

void increment(int* size, int incrementValue) {
    (*size) += incrementValue;
};

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

void decrementCardFreq(cardObj* arrObj, int arrObjDim, tessera insertedTessera, int quantitàInserita) {
    for (size_t i = 0; i < arrObjDim; i++)
    {
        if ((arrObj[i].card.num1 == insertedTessera.num1) && (arrObj[i].card.num2 == insertedTessera.num2))
        {
            int count = 0;
            while (count < quantitàInserita)
            {
                arrObj[i].freq--;
                count++;
            }
        }
    }
};

void pushHeadAI(tessera* table, tessera t, int* pointer)
{
    table[*pointer] = t;
    *pointer += 1;
};

void insert(tessera* AiCards, int tabSize, tessera mostFreq, tessera* table, int* ptrTable, int* AICardSize, int freqTessera) {
    int count = 0;
    for (size_t i = 0; i < tabSize; i++)
    {
        if (mostFreq.num1 == AiCards[i].num1 && mostFreq.num2 == AiCards[i].num2)
        {
            count++;
            if (count % 2 == 0) {
                tessera tes = rotateAI(AiCards[i]);
                // printf("Tessera ruotata: [%d|%d]", tes.num1, tes.num2);
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

};

void insertAfterFirst(tessera* AiCards, int tabSize, tessera t, tessera* table, int* ptrTable, int* AICardSize, int freqTessera, int* tableSizeCur) {
    int count = 0;
    for (size_t i = 0; i < tabSize; i++)
    {
        if (t.num1 == AiCards[i].num1 && t.num2 == AiCards[i].num2)
        {
            count++;
            bool insertable = isInsertable(table, AiCards[i], ptrTable);
            if (!insertable) {
                tessera tes = rotateAI(AiCards[i]);
                // printf("Tessera ruotata: [%d|%d]", tes.num1, tes.num2);
                pushHeadAI(table, tes, ptrTable);
                increment(tableSizeCur, 1);

            }
            else {
                pushHeadAI(table, AiCards[i], ptrTable);
                increment(tableSizeCur, 1);
            }
        }


    }
    for (size_t i = 0; i < freqTessera; i++)
    {
        removeTessera(t, AiCards, AICardSize);
    }

};

void insertDX(int* currentTableSize, tessera* AiCards, int* currentAiCards, tessera t, tessera* table) {
    for (size_t i = 0; i < *currentAiCards; i++)
    {
        if ((AiCards[i].num1 == t.num1) && (AiCards[i].num2 == t.num2)) {
            table[*currentTableSize] = AiCards[i];
            (*currentAiCards)++;
        }
    }

}

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
};

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

    // printf("La size: %d\n", size);

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
};

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
};

tessera getTessera(cardObj* arrObj, int indexObj) {
    return arrObj[indexObj].card;
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
};

int getIndexCard(int num, cardObj* arr, int* sizeCardObj) {
    int index = 0;
    int freq = 0;
    for (size_t i = 0; i < *sizeCardObj; i++)
    {
        if (arr[i].card.num1 == num || arr[i].card.num2 == num) {
            if (arr[i].freq > freq) {
                index = i;
            }
            else if (arr[index].freq == arr[i].freq)
            {
                int cardSum = arr[index].card.num1 + arr[index].card.num2;
                int currentCardSum = arr[i].card.num1 + arr[i].card.num2;
                if (cardSum > currentCardSum) {
                    return index;
                }
                else {
                    index = i;
                    return index;
                }
            }
        }
    }
    return index;
};

bool isInsertable(tessera* table, tessera toInsert, int* indexTable) {
    if (indexTable == 0 && table[0].num1 == toInsert.num2) {
        return true;
    }
    else if (indexTable > 0)
    {
        if (table[*indexTable - 1].num2 == toInsert.num1) {
            return true;
        };
    }


    return false;
}



    /*
    for (int i = 0; i < *numberOfcards; i++) {
        printf("\n32card -> [%d|%d] _ freq -> %d\n", aiCards1[i].num1, aiCards1[i].num2, freq[i]);
    }
    */