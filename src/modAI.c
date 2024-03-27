#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"
#include "check.h"
#include "ai.h"


void modAI(tessera* alltessere, int tableSize) {
    // 1: setting IA
   // Creazione tavolo e tessere
    tessera* table = creaTable(tableSize);
    int indexTableAI = 0;
    //> Tessere inserite nel tavolo
    int currentTableSize = 0;

    //* Carte in mano all'ia
    tessera* AiCards = giveTessereToPlayer(alltessere, tableSize);
    int AicardSize = tableSize;
    int* ptrAiCardSize = &AicardSize;
    //Ciclo while per continuare finche la mano del giocatore non è vuota o non ci sono piu combinazioni

    // printTessere(AiCards, tableSize);
    // puts("\n");
    sortCards(AiCards, tableSize);
    // Ordinmanto e Registro frequenze tessere
    int most = findMostFrequent(AiCards, tableSize);

    //> Ottengo frequenze totali singoli numeri;
    freq* ptrFreq = getFreq();

    printTessere(AiCards, tableSize);

    int sizeObj = findDim(AiCards, tableSize);
    cardObj* arrayObj = createArray(AiCards, tableSize, sizeObj);


    // 2: partita IA
    //trova la tessera più frequente

    int indexCard = obtainCard(arrayObj, sizeObj);
    int freqIndexCard = arrayObj[indexCard].freq;
    tessera mostFreq = getTessera(arrayObj, indexCard);

    insert(AiCards, tableSize, mostFreq, table, &indexTableAI, ptrAiCardSize, freqIndexCard);

    int quantitaInserita = tableSize - AicardSize;
    increment(&currentTableSize, quantitaInserita);
    printf("Grandezza attuale tavolo %d\n", currentTableSize);
    //printf("Hai inserito %d carte", quantitaInserita);
    //> Decremento le frequenze delle tessere
    decrementCardFreq(arrayObj, sizeObj, mostFreq, quantitaInserita);

    //>Mi Occupo dell ramo destro
    int rightNum = table[quantitaInserita - 1].num2;
    // printf("%d numero piu a destra", rightNum);


    int ind = getIndexCard(rightNum, arrayObj, &sizeObj);

    printf("%d|%d\n", arrayObj[ind].card.num1, arrayObj[ind].card.num2);
    //for (size_t i = 0; i < sizeObj; i++)
    //{
    //    printf("%d|%d x %d\n", arrayObj[i].card.num1, arrayObj[i].card.num2, arrayObj[i].freq);
    //}


    puts("\n\n");

    printTessere(table, tableSize);

    puts(" ");
    printTessere(AiCards, tableSize);

    // bool canFollow = canGoNext(table, AiCards, &indexTableAI, ptrAiCardSize);

    // int mostFr = findMostFrequent(AiCards, AicardSize);
    // int index = obtainCard(arrayObj, sizeObj);

    // printf("%d|%d", arrayObj[index].card.num1, arrayObj[index].card.num2);

    // printf("Il numero piu frequente è %d\n", mostFr);




    // printf("%d", *ptrAiCardSize);
    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
    free(AiCards);
    free(arrayObj);

    // FINE
}
