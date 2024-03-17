#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "domino.h"
#include "check.h"

void modAI(tessera* alltessere, int tableSize) {

    tessera* table = creaTable(tableSize);

    tessera* tableCard = giveTessereToPlayer(alltessere, tableSize);
    printTessere(tableCard, tableSize);

    int most_freq = findMostFrequent(tableCard, tableSize);
    // printf("%d", most_freq);



    free(table);
    free(tableCard);
}