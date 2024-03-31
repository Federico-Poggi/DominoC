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
    //int mossa1 = 1;
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
        aiGame(table, aiCards1, &indexTable, &numberOfcards, tableSize);
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        printf("\033[1;32mIl tavolo al momento presenta le tessere:\n\n\033[0m");  
        printTessere(aiCards1, tableSize);
        puts("");
        style();
        //mossa1 = 0;
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
    free(table);
    free(aiCards1);
}

void aiGame (tessera* table, tessera* aiCards1, int* indexTable, int* numberOfcards, int tableSize) {
    //crea array ferquenze locale
    int freq[*numberOfcards];
    inizializza (aiCards1, freq, *numberOfcards);
}
