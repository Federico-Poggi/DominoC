#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "check.h"
#include "domino.h"
void mod1(tessera *std, int numberOfcards);

// FUNZIONE MADRE GIOCO
int main()
{
    // SEME NUMERI RANDOMICI
    srand(time(NULL));

    // VARIABILI ITERAZIONE MAIN
    bool playAgain = true;
    bool changeResp = true;
    // VARIABILI GIOCO MAIN
    tessera *std = stdTessere();
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
            // style();
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

// MODALITA' DI GIOCO MENU'
int playMode()
{
    int mod = 0;
    printf("Inserisci la modalita di gioco:");
    puts("\n");
    printf("1: Modalità classica interattiva\n2: Modalità AI\n3:");
    puts("\n");
    printf("Inserisci il numero della modalità desiderata [1, 2, 3]: ");
    do
    {
        scanf("%d", &mod);
        // ERRORE MODALITA';
        if (mod > 3 || mod < 0)
        {
            puts(" ");
            // printf("Modalità inserita non valida!\n");
            error("Modalità inserita non valida! \n");
            printf("Inserisci una modalità valida [1, 2, 3]: ");
        };

    } while (mod > 3 || mod < 0);
    puts(" ");
    // printf("Sono uscito");
    return mod;
};
