#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"
#include "check.h"


void mod1(tessera* std, int numberOfcards);

/**
 * @brief Funzione principale del gioco.
 *
 * @return int
 */

 // FUNZIONE MADRE GIOCO
int main()
{
    // SEME NUMERI RANDOMICI
    srand(time(NULL));

    // VARIABILI ITERAZIONE MAIN
    bool playAgain = true;
    bool changeResp = true;
    // VARIABILI GIOCO MAIN
    tessera* std = stdTessere();
    int risposta = 0;
    int numberOfcards = 0;
    int tableSize = 0;

    // INTRODUZIONE


    printf("\n\033[1;31mB\033[1;32mE\033[1;33mN\033[1;34mV\033[1;35mE\033[1;36mN\033[1;37mU\033[0m\033[1;31mT\033[1;32mO\033[1;33m \033[1;34mI\033[1;35mN\033[1;36m \033[1;37mD\033[1;31mO\033[1;32mM\033[1;33mI\033[1;34mN\033[1;35mO\033[0m\n\n");

    style();
    while (playAgain)
    {

        puts("");
        int modalita = playMode();

        if (modalita == 2) {
            bool con2 = true;
            do {
                printf("Inserisci il numero di tessere da creare (min 10): ");
                scanf("%d", &tableSize);
                if (tableSize < 10) {
                    puts("");
                    error("Numero di tessere non valido");
                    puts("\n");
                    con2 = false;
                }
                else {
                    con2 = true;
                }
            } while (con2 == false);
        }

        if (modalita == 1) {
            bool con = true;
            do {
                printf("Inserisci il numero di tessere con cui giocare (min 10; max 100): ");
                scanf("%d", &tableSize);
                if (tableSize < 10 || tableSize > 100) {
                    puts("");
                    error("Numero di tessere non valido");
                    puts("\n");
                    con = false;
                }
                else {
                    con = true;
                }
            } while (con == false);
            numberOfcards = tableSize;
        }

        puts(" ");
        style();
        switch (modalita)
        {
        case 1:
            printf("\n\033[1;34mModalità: %d\033[0m\n", modalita);
            mod1(std, numberOfcards);
            break;
        case 2:
            printf("\033[1;33m\nModalità: %d\n\033[0m", modalita);
            modAI(std, tableSize);
            break;
            /*
            case 3:
                printf("\nModalità: %d\n", modalita);
                break;
            */
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


    free(std);
    // FINE GIOCO
    return 0;
}
/**
 * @brief \b Modalità \b di \b gioco
 *
 * @li \b 1- \b Modalita \b interattiva
 * @li \b 2- \b Modalità \b AI
 * @return \b Int modalità scelta
 */
 // MODALITA' DI GIOCO MENU'
int playMode()
{
    int mod = 0;
    printf("Inserisci la modalita di gioco:");
    puts("\n");
    printf("\033[1;34m1: Modalità classica interattiva\033[0m\n\033[1;33m2: Modalità AI\033[0m");
    puts("\n");
    printf("Inserisci il numero della modalità desiderata [1, 2]: ");
    do
    {
        scanf("%d", &mod);
        // ERRORE MODALITA';
        if (mod > 2 || mod < 0)
        {
            puts(" ");
            error("Modalità inserita non valida! \n");
            printf("Inserisci una modalità valida [1, 2]: ");
        };

    } while (mod > 3 || mod < 0);
    return mod;
};
