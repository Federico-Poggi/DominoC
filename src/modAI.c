#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"
#include "check.h"
#include "ai.h"
#include <assert.h>


void modAI(tessera* std, int numberOfcards) {
    // VARIABILI GENERALI MDOALITA' 1
    bool playerMode = false;
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
    printf("\033[1;33m\nAll'AI verranno assegnate %d tessere.\nLa partita sarà automatica e seguira le calssiche regole del domino:\nI numeri dei lati adiacenti tra due tessere devono essere identici.\n\n\033[0m", numberOfcards);
    style();

    //int end = 5;

    //int k = 3; variabile controllo iterazione caso verifica 
    do
    {
        printf("\033[1;32m\nLe tessere in mano all'AI al momento sono:\n\n\033[0m");
        printTessere(aiCards1, numberOfcards);
        puts("");
        aiGame(table, aiCards1, &indexTable, &numberOfcards, tableSize, &mossa1Ai);
        //end--;
        mossa1Ai = 0;
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        printf("\033[1;32mIl tavolo al momento presenta le tessere:\n\n\033[0m");
        printTessere(table, tableSize);
        puts("");
        style();
        canFollow = canGoNext(table, aiCards1, &indexTable, numberOfcards, playerMode);
        if (!canFollow)
        {
            break;
        }

    } while (numberOfcards);

    playerPoints = endPoints(table, tableSize);

    printf("\n\033[1;35mCompletato!\033[0m Sono stati totalizzati: \033[1;32m%d punti\033[0m", playerPoints);

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    mossa1Ai = 1;
    free(table);
    free(aiCards1);
}

void aiGame(tessera* table, tessera* aiCards1, int* indexTable, int* numberOfcards, int tableSize, int* mossa1) {
    //crea array ferquenze locale
    int freq[tableSize];
    inizializza(aiCards1, freq, tableSize);


    // MOSSA 1
    if (*mossa1 == 1) {
        //code for mossa 1
        int index = findfirst(aiCards1, freq, tableSize);
        printf("\033[1;32mCarta scelta: [%d|%d]\nNel mazzo compare: %d volte\n\n\033[0m", aiCards1[index].num1, aiCards1[index].num2, freq[index]);
        int num = freq[index];
        if (aiCards1[index].num1 == aiCards1[index].num2) {
            while (num) {
                pushHead(table, aiCards1, index, indexTable);
                *numberOfcards -= 1;
                aiCards1[index].num1 = 0;
                aiCards1[index].num2 = 0;
                freq[index] = 0;
                pop_back(aiCards1, index, tableSize);
                //++index;
                --num;
            }
        }
        else {
            bool change = false;
            while (num) {
                if (change == false) {
                    pushHead(table, aiCards1, index, indexTable);
                    *numberOfcards -= 1;
                    change = true;
                }
                else {
                    rotate(aiCards1, index);
                    pushHead(table, aiCards1, index, indexTable);
                    *numberOfcards -= 1;
                    change = false;
                }
                aiCards1[index].num1 = 0;
                aiCards1[index].num2 = 0;
                freq[index] = 0;
                pop_back(aiCards1, index, tableSize);
                //++index;
                --num;
            }
        }
    }
    else {
        // MOSSE SUCESSIVE
        int dx = table[(*indexTable) - 1].num2;
        int indexDX = findDX_SX(aiCards1, freq, tableSize, dx);
        bool couldEnter = sohuldEnter(aiCards1, indexDX, dx);
        if (couldEnter == true) {
            //RAMO DX
            printf("\033[1;32mCarta scelta: [%d|%d]\nNel mazzo compare: %d volte\n\n\033[0m", aiCards1[indexDX].num1, aiCards1[indexDX].num2, freq[indexDX]);
            int num = freq[indexDX];

            bool isRotated = false;
            if (aiCards1[indexDX].num1 != table[(*indexTable) - 1].num2) {
                isRotated = true;
            }

            bool change = false;
            while (num) {
                if (change == false) {
                    if (isRotated == true) {
                        rotate(aiCards1, indexDX);
                    }
                    pushHead(table, aiCards1, indexDX, indexTable);
                    *numberOfcards -= 1;
                    change = true;
                }
                else {
                    if (isRotated == true) {
                        rotate(aiCards1, indexDX);
                    }
                    rotate(aiCards1, indexDX);
                    pushHead(table, aiCards1, indexDX, indexTable);
                    *numberOfcards -= 1;
                    change = false;
                }
                aiCards1[indexDX].num1 = 0;
                aiCards1[indexDX].num2 = 0;
                freq[indexDX] = 0;
                pop_back(aiCards1, indexDX, tableSize);
                //++indexDX;
                --num;
            }
        }
        else {
            //RAMO SX
            int sx = table[0].num1;
            int indexSX = findDX_SX(aiCards1, freq, tableSize, sx);
            bool canEnter = sohuldEnter(aiCards1, indexSX, sx);
            if (canEnter == false) {
                bool ass = true;
                if (ass == true) {
                    printf("\n\nDevo fare la first match\n\n");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                //printf("L'indice uscito è %d\n", indexSX);
                int num = freq[indexSX];
                printf("\033[1;32mCarta scelta: [%d|%d]\nNel mazzo compare: %d volte\n\n\033[0m", aiCards1[indexSX].num1, aiCards1[indexSX].num2, freq[indexSX]);

                bool isRotated = false;
                if (aiCards1[indexSX].num2 != table[0].num1) {
                    isRotated = true;
                }

                bool change = false;
                while (num) {
                    if (change == false) {
                        if (isRotated == true) {
                            rotate(aiCards1, indexSX);
                        }
                        pushFooter(table, tableSize, aiCards1, indexSX, indexTable);
                        *numberOfcards -= 1;
                        change = true;
                    }
                    else {
                        if (isRotated == true) {
                            rotate(aiCards1, indexSX);
                        }
                        rotate(aiCards1, indexSX);
                        pushFooter(table, tableSize, aiCards1, indexSX, indexTable);
                        *numberOfcards -= 1;
                        change = false;
                    }
                    aiCards1[indexSX].num1 = 0;
                    aiCards1[indexSX].num2 = 0;
                    freq[indexSX] = 0;
                    pop_back(aiCards1, indexSX, tableSize);
                    //++indexDX;
                    --num;
                }
            }

        };
    }
}

