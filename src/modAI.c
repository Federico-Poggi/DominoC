#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"
#include "check.h"
#include "ai.h"


void modAI(tessera* std, int numberOfcards) {
    // VARIABILI GENERALI MDOALITA' 1
    int playerPoints = 0;
    int indexTable = 0;
    //int choice = 0;
    bool mossa1Ai = true;
    int tableSize = numberOfcards;
    bool canFollow = true;
    tessera* table = creaTable(numberOfcards); // ARRAY TAVOLO
    tessera* aiCards1 = giveTessereToPlayer(std, numberOfcards);
    sortCards(aiCards1, tableSize);
    // printf(" indirizzo di partenza: %p\n\n", playerCards1);

    // INTRODUZIONE GIOCO (COMPARE SOLO ALLA PRIMA PARTITA)
    printf("\nAl giocatore verranno assegnate %d tessere.\nL'obiettivo è quello di disporre le tessere sul tavolo scondo la regola:\nI numeri dei lati adiacenti tra due tessere devono essere identici.\n\n", numberOfcards);
    style();

    //int k = 3; variabile controllo iterazione caso verifica 
    do
    {   
        //printTessere(aiCards1, tableSize);
        //puts("\n");
        aiGame(table, aiCards1, &indexTable, &numberOfcards, tableSize, &mossa1Ai);
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        printf("\033[1;32mIl tavolo al momento presenta le tessere:\n\n\033[0m");  
        printTessere(aiCards1, tableSize);
        puts("");
        style();
        numberOfcards -= 1;
        canFollow = canGoNext(table, aiCards1, &indexTable, numberOfcards);
        if (!canFollow)
        {
            break;
        }

    } while (numberOfcards); 

    playerPoints = endPoints(table, tableSize);

    printf("\n\033[1;35mComplimenti!\033[0m Hai totalizzato: \033[1;32m%d punti\033[0m", playerPoints);

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    mossa1Ai = true; 
    free(table);
    free(aiCards1);
}

void aiGame (tessera* table, tessera* aiCards1, int* indexTable, int* numberOfcards, int tableSize, bool* mossa1) {
    //crea array ferquenze locale
    int freq[*numberOfcards];
    inizializza (aiCards1, freq, *numberOfcards);

    /*
    for (int i = 0; i < *numberOfcards; i++) {
        printf("\n32card -> [%d|%d] _ freq -> %d\n", aiCards1[i].num1, aiCards1[i].num2, freq[i]);
    }
    */

    if (*mossa1) {
        //code for mossa 1
        int index = findfirst(aiCards1, freq, *numberOfcards);
        //gestione push
        if (aiCards1[index].num1 == aiCards1[index].num2) {
            int num = freq[index];
            while (num != 1) {
                pushHead(table, aiCards1, index, indexTable);
                *numberOfcards -= 1;
                aiCards1 = newPlayercards(aiCards1, *numberOfcards, index);
                --num;
            }
        }
        *mossa1 = false;
    }
}
