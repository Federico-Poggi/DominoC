#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Headers/header_domino.h"
#include "Headers/check.h"

void mod1(tessera *std, int numberOfcards);
//---------------------------------------------------------------//
int main()
{
    // SEME NUMERI RANDOMICI
    srand(time(NULL));

    // VARIABILI MAIN
    tessera *std = stdTessere();
    bool playAgain = true;
    bool changeResp = true;
    int risposta = 0;
    int numberOfcards = 28;

    // INTRODUZIONE
    style();
    printf("\nBENVENUTO IN DOMINO\n\n");
    style();
    while (playAgain)
    {
        puts("");
        int modalita = playMode();
        style();
        switch (modalita)
        {
        case 1:
            printf("\nModalità: %d\n", modalita);
            mod1(std, numberOfcards);
            break;
        case 2:
            printf("\nModalità: %d\n", modalita);
            break;
        case 3:
            printf("\nModalità: %d\n", modalita);
            break;
        default:
            error("Modalità non valida\n");
        }
        // Possibilità di giocare nuovamente
        do
        {
            style();
            printf("\nVuoi giocare ancora?\n\n1: Si\n2: No\n\nHai scelto l'opzione: ");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                changeResp = false;
                puts("");
                style();
                break;
            case 2:
                changeResp = false;
                playAgain = false;
                break;
            default:
                error("Comando non valido. Scegli tra le opzioni disponibili.\n\n");
                ;
            }
        } while (changeResp);
    }
    puts("");
    style();

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(std);
    // FINE GIOCO
    return 0;
}

// MODALITA' CLASSICA
void mod1(tessera *std, int numberOfcards)
{
    // VARIABILI MODALITA' 1
    int pointer = 0; // PUNTATORE ULTIMA TESSERA INSERITA ARRAY
    int rotateQ = 0;
    int choice = 0;
    tessera *table = creaTable(numberOfcards);

    printf("Tessere nella tua mano :");
    puts("\n");

    tessera *playerCards1 = giveTessereToPlayer(std, numberOfcards);

    printTessere(playerCards1, numberOfcards);
    puts("\n");

    choice = chooseCard(playerCards1);
    printf("[%d|%d] ", playerCards1[choice].num1, playerCards1[choice].num2);

    puts("\nVuoi ruotare la tessera selezionata?\n\n1-Si, ruotala\n2-No, lasciala così");
    do
    {
        printf("Hai scelto l'opzione: ");
        scanf("%d", &rotateQ);
        if (rotateQ < 1 || rotateQ > 2)
        {
            error("Comando non valido. Scegli tra le opzioni disponibili.\n");
        }
    } while (rotateQ < 1 || rotateQ > 2);

    if (rotateQ == 1)
    {
        rotate(playerCards1, choice);
    }
    printf("[%d|%d]\n\n", playerCards1[choice].num1, playerCards1[choice].num2);

    pushHead(table, playerCards1, choice, &pointer);
    printTessere(table, numberOfcards);
    printf("\n%d\n", pointer);

    pushFooter(table, numberOfcards, playerCards1, choice, &pointer);
    printTessere(table, numberOfcards);
    printf("\n%d\n", pointer);

    puts("\n");

    // FREE ALL MALLOC CREATED!!!
    // I WANT TO BREAK FREE!!!
    free(table);
}
