#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"

void mod1(tessera *std, int numberOfcards)
{
    // VARIABILI GENERALI MDOALITA' 1
    int indexTable = 0;
    int choice = 0;
    int mossa1 = 1;
    int tableSize = numberOfcards;
    bool canFollow = true;
    tessera *table = creaTable(numberOfcards); // ARRAY TAVOLO
    tessera *playerCards1 = giveTessereToPlayer(std, numberOfcards);
    // printf(" indirizzo di partenza: %p\n\n", playerCards1);

    // INTRODUZIONE GIOCO (COMPARE SOLO ALLA PRIMA PARTITA)
    printf("\nAl giocatore verranno assegnate %d tessere.\nL'obiettivo è quello di disporre le tessere sul tavolo scondo la regola:\nI numeri dei lati adiacenti tra due tessere devono essere identici.\n\n", numberOfcards);
    style();

    do
    {
        mossa(table, playerCards1, &indexTable, &numberOfcards, &choice, mossa1, tableSize);
        playerCards1 = newPlayercards(playerCards1, numberOfcards, choice);
        // LA SVOLGIAMO QUI PER NON PERDERCI INDIRIZZZI DI MEMORIA PER LE FREE
        printTessere(table, tableSize);
        puts("");
        style();
        mossa1 = 0;
        numberOfcards -= 1;
        canFollow = canGoNext(table, playerCards1, &indexTable, numberOfcards);
        if (!canFollow)
        {
            break;
        }

    } while (numberOfcards); // per ora gioca finché hai carte

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
    free(playerCards1);
}

// MOSSA MODALITA' CLASSICA
void mossa(tessera *table, tessera *playerCards1, int *indexTable, int *numberOfcards, int *choiceptr, int mossa1, int tableSize)
{

    // VARIABILI SCELTE PLAYER 1
    bool playAgain = true;
    bool changeResp = true;
    bool checkValue = false;
    bool isIsertable = false;
    int pushQuestion = 0;
    int risposta = 0;

    while (playAgain)
    {
        // VARIABILI SCELTE PLAYER 2
        int rotateQuestion = 0;
        *choiceptr = 0;

        // MOSSA 1
        // STAMPA TESSERE MANO GIOCATORE
        puts("");
        printTessere(playerCards1, *numberOfcards);
        puts("");

        // RICHIESTA TESSERA DA SCEGLIERE
        *choiceptr = chooseCard(playerCards1, numberOfcards);
        printf("\n[%d|%d]", playerCards1[*choiceptr].num1, playerCards1[*choiceptr].num2);
        puts("\n");

        // Questa ritorna True se è possibile inserire la tessara dentro al tavolo al contrario TORNA FALSE;
        checkValue = insertCheck(table, playerCards1, indexTable, choiceptr);
        if (!checkValue)
        {
            continue;
        }

        // CONTROLLE SE LA TESSERA PUO ESSERE INSERITA ATTRAVERSO IL CONTROLLO DEI DUE NUMERI DELLA TESSERA SCELTA
        do
        {
            // RICHIESTA ROTAZIONE
            puts("\nVuoi ruotare la tessera selezionata?\n\n1-Si, ruotala\n2-No, lasciala così");

            do
            {
                printf("\nHai scelto l'opzione: ");
                scanf("%d", &rotateQuestion);
                if (rotateQuestion < 1 || rotateQuestion > 2)
                    error("Comando non valido. Scegli tra le opzioni disponibili.\n");
            } while (rotateQuestion < 1 || rotateQuestion > 2);

            if (rotateQuestion == 1)
                rotate(playerCards1, *choiceptr);
            printf("\n[%d|%d]\n", playerCards1[*choiceptr].num1, playerCards1[*choiceptr].num2);

            if (mossa1 == 0) // SCELTA DOVE VUOI PUSHARE
            {
                // RICHIESTA PUSH
                puts("\nDove vuoi inserire la tessera selezionata?\n\n1-A destra\n2-A sinistra");
                do
                {
                    printf("\nHai scelto l'opzione: ");
                    scanf("%d", &pushQuestion);
                    if (pushQuestion < 1 || pushQuestion > 2)
                        error("Comando non valido. Scegli tra le opzioni disponibili.\n");
                } while (pushQuestion < 1 || pushQuestion > 2);
            }

            bool check = checkInsertable(table, playerCards1, indexTable, choiceptr, pushQuestion, mossa1);
            if (check)
            {
                printf("\033[1;32mI valori sono uguali può essere inserita\n \033[0m\n");
                isIsertable = check;
            }
            else if (isIsertable == false && rotateQuestion == 1)
            {
                printf("\033[1;31mI valori non sono uguali può essere inserita\n \033[0m\n");
                // Se è stata ruotata resettarla allo stato precedente
                rotate(playerCards1, *choiceptr);
                // printf("Tessera [%d|%d]", playerCards1[*choiceptr].num1, playerCards1[*choiceptr].num2);
                // puts(" ");
            }

        } while (!isIsertable);

        do
        {
            printf("\nConfermi le scelte fatte?\n\n1: Si\n2: No\n\nHai scelto l'opzione: ");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                changeResp = false;
                playAgain = false;
                puts("");
                break;
            case 2:
                changeResp = false;
                puts("");
                style();
                break;
            default:
                error("Comando non valido. Scegli tra le opzioni disponibili.\n");
                changeResp = true;
            }
        } while (changeResp);
    }

    if (mossa1 == 1)
    {
        pushHead(table, playerCards1, *choiceptr, indexTable);
    }
    if (pushQuestion == 1)
    {
        pushHead(table, playerCards1, *choiceptr, indexTable);
    }
    if (pushQuestion == 2)
    {
        pushFooter(table, tableSize, playerCards1, *choiceptr, indexTable);
    }

    checkValue = false;
}