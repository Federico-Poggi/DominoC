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
    // printf("\033[1;31m\033[0m ");        // rosso
    // printf("\033[1;32mVerde\033[0m ");   // verde
    // printf("\033[1;33mGiallo\033[0m ");  // giallo
    // printf("\033[1;34mBlu\033[0m ");     // blue
    // printf("\033[1;35mViola\033[0m ");   // viola
    // printf("\033[1;36mAzzurro\033[0m "); // azzurro
    // printf("\033[1;37mBianco\033[0m\n"); // Bianco

    printf("\n\033[1;31mB\033[1;32mE\033[1;33mN\033[1;34mV\033[1;35mE\033[1;36mN\033[1;37mU\033[0m\033[1;31mT\033[1;32mO\033[1;33m \033[1;34mI\033[1;35mN\033[1;36m \033[1;37mD\033[1;31mO\033[1;32mM\033[1;33mI\033[1;34mN\033[1;35mO\033[0m\n\n");

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
            error("Modalità inserita non valida! \n");
            printf("Inserisci una modalità valida [1, 2, 3]: ");
        };

    } while (mod > 3 || mod < 0);
    puts(" ");
    // printf("Sono uscito");
    return mod;
};
