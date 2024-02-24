#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "../include/domino.h"
#include "../include/check.h"

void mod1(tessera *std, int numberOfcards)
{
    // VARIABILI GENERALI MDOALITA' 1
    int indexTable = 0;
    int choice = 0;
    int mossa1 = 1;
    int tableSize = numberOfcards;
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
        // printf("indirizzo finale: %p\n\n", playerCards1);
        printTessere(table, tableSize);
        puts("");
        style();
        mossa1 = 0;
        // numberOfcards -= 1;
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
        if (checkValue)
        {
            puts("TRUE");
            *numberOfcards -= 1;
        }
        else
        {
            puts("FALSE");
            numberOfcards = numberOfcards;
            continue;
        }

        // CONTROLLE SE LA TESSERA PUO ESSERE INSERITA ATTRAVERSO IL CONTROLLO DEI DUE NUMERI DELLA TESSERA SCELTA

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