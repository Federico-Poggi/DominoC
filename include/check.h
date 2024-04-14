#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "domino.h"

#ifndef CHECK_H
#define CHECK_H

bool insertCheck(tessera* table, tessera* playercards, int* indexTable, int* choice);

bool checkInsertable(tessera* table, tessera* playercards, int* indexTable, int* choice, int dxOrSx, int mossa1);

bool canGoNext(tessera* table, tessera* playCards, int* indexTable, int numberOfCards, bool aiMode);

#endif // !CHECK_H