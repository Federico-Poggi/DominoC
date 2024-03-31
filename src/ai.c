#include "ai.h"
#include <stdio.h>
#include <stdbool.h>

void swap(tessera* AiCards1, tessera* AiCards2){
    tessera temp1 = *AiCards1;
    *AiCards1 = *AiCards2;
    *AiCards2 = temp1;
}

void sortCards(tessera* AiCards, int Size){
    // Sort num1
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if (AiCards[j].num1 > AiCards[j + 1].num1){
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

void inizializza (tessera* aiCards1, int freq[], int numberOfCards){
    int count = 0;
    for (int i = 0; i < numberOfCards; ++i) {
        for (int j = 0; j < numberOfCards; ++j) {
            if ((aiCards1[i].num1 == aiCards1[j].num1) && (aiCards1[i].num2 == aiCards1[j].num2)) {
                count++;
            }
        }
        freq[i] = count;
    }
}