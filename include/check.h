#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"

#ifndef CHECK_H
#define CHECK_H

typedef struct {
    int num;
    int frequency;
} freq;


bool insertCheck(tessera* table, tessera* playercards, int* indexTable, int* choice);

bool checkInsertable(tessera* table, tessera* playercards, int* indexTable, int* choice, int dxOrSx, int mossa1);

bool canGoNext(tessera* table, tessera* playCards, int* indexTable, int numberOfCards);

int findMostFrequent(tessera* table, int tableSize);

// * funzioni di servizio per ordinare l'array in maniera decrescente num1
void merge(tessera tempTable[], int left, int right, int middle);
void sortMerge(tessera tempTable[], int left, int right);

#endif // !CHECK_H