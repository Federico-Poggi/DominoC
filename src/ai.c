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
    int count;
    for (int i = 0; i < numberOfCards; ++i) {
        count = 0;
        for (int j = 0; j < numberOfCards; ++j) {
            if ((aiCards1[i].num1 == aiCards1[j].num1) && (aiCards1[i].num2 == aiCards1[j].num2)) {
                count++;
            }
        }
        freq[i] = count;
    }
}

int findfirst(tessera* aiCards1, int freq[], int numberOfcards) {
    int out = 0;
    int max = freq[0];
    for (int i = 1; i < numberOfcards; ++i) {
        if (freq[i] > max) {
            max = freq[i];
            out = i;
        }
        if (freq[i] == max) {
            if ((aiCards1[i].num1 + aiCards1[i].num2) > (aiCards1[out].num1 + aiCards1[out].num2)) {
                out = i;
            }
        }
    }
    printf("\ncard -> [%d|%d] _ freq -> %d\n", aiCards1[out].num1, aiCards1[out].num2, freq[out]);
    return out;
}