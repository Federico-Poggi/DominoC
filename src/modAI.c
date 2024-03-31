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
    int  mossa1Ai = 1;
    int tableSize = numberOfcards;
    bool canFollow = true;
    tessera* table = creaTable(numberOfcards); // ARRAY TAVOLO
    tessera* aiCards1 = giveTessereToPlayer(std, numberOfcards);
    sortCards(aiCards1, tableSize);
    // printf(" indirizzo di partenza: %p\n\n", playerCards1);

    // INTRODUZIONE GIOCO (COMPARE SOLO ALLA PRIMA PARTITA)
    printf("\nAl giocatore verranno assegnate %d tessere.\nL'obiettivo è quello di disporre le tessere sul tavolo scondo la regola:\nI numeri dei lati adiacenti tra due tessere devono essere identici.\n\n", numberOfcards);
    style();

    //int sesso = 5;

    //int k = 3; variabile controllo iterazione caso verifica 
    do
    {   
        printTessere(aiCards1, numberOfcards);
        puts("\n");
        aiGame(table, aiCards1, &indexTable, &numberOfcards, tableSize, &mossa1Ai);
        //sesso--;
        mossa1Ai = 0;
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        printf("\033[1;32mIl tavolo al momento presenta le tessere:\n\n\033[0m");  
        printTessere(table, tableSize);
        puts("");
        style();
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
    mossa1Ai = 1; 
    free(table);
    free(aiCards1);
}

void aiGame (tessera* table, tessera* aiCards1, int* indexTable, int* numberOfcards, int tableSize, int* mossa1) {
    //crea array ferquenze locale
    int freq[tableSize];
    inizializza (aiCards1, freq, tableSize);


    // MOSSA 1
    if (*mossa1 == 1) {
        //code for mossa 1
        int index = findfirst(aiCards1, freq, tableSize);
        int num = freq[index];
        if (aiCards1[index].num1 == aiCards1[index].num2) {
            while (num) {
                pushHead(table, aiCards1, index, indexTable);
                *numberOfcards -= 1;
                aiCards1[index].num1 = 0;
                aiCards1[index].num2 = 0;
                freq[index] = 0;
                ++index;
                --num;
            }
        }
        else {
            bool change = false;
            while (num) {
                if (change == false) {
                    rotate (aiCards1, index);
                    pushHead(table, aiCards1, index, indexTable);
                    *numberOfcards -= 1;
                    change = true;
                }
                else {
                    pushHead(table, aiCards1, index, indexTable);
                    *numberOfcards -= 1;
                    change = false;
                }
                aiCards1[index].num1 = 0;
                aiCards1[index].num2 = 0;
                freq[index] = 0;
                ++index;
                --num;
            }
        }
    }
    else {   
    // MOSSE SUCESSIVE DX
    int dx = table[(*indexTable) - 1].num2;
    int indexDX = findDX (aiCards1, freq, tableSize, dx);
    int num = freq[indexDX];

    bool change = false;
    while (num) {
        if (change == false) {
            if (aiCards1[indexDX].num1 != table[(*indexTable) - 1].num2) {
                rotate (aiCards1, indexDX);
            }
            pushHead(table, aiCards1, indexDX, indexTable);
            *numberOfcards -= 1;
            change = true;
        }
        else {
            rotate (aiCards1, indexDX);
            pushHead(table, aiCards1, indexDX, indexTable);
            *numberOfcards -= 1;
            change = false;
        }
        aiCards1[indexDX].num1 = 0;
        aiCards1[indexDX].num2 = 0;
        freq[indexDX] = 0;
        ++indexDX;
        --num;
    }

    }
}
