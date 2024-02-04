#include <stdio.h>
#include <string.h>

//-----------------------------FUNZIONI---------------------------//
void style();
int playMode();
void error(char *message);
//---------------------------------------------------------------//
int main()
{
    // INTRODUZIONE
    printf("BENVENUTO IN DOMINO\n");
    style();
    int modalita = playMode();
    style();
    switch (modalita)
    {
    case 1:
        printf("Modalità: %d\n", modalita);
        break;
    case 2:
        printf("Modalità: %d\n", modalita);
        break;
    case 3:
        printf("Modalità: %d\n", modalita);
        break;
    default:
        error("ERRORE\n");
    }
    return 0;
};

void style()
{
    for (char k = 0; k <= 18; ++k)
    {
        printf("-");
    }
    puts(" ");
};
// MODALITA' DI GIOCO
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

void error(char *message)
{
    printf("ERRORE: %s", message);
};

// MODALITA' CLASSICA