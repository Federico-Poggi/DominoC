
#ifndef DOMINO_H
#define DOMINO_H

typedef struct
{
    int num1;
    int num2;
} tessera;


extern const int MAX_VAL_TESSERA;
void style();
void error(const char* message);
tessera* stdTessere();
tessera* creaTable(int numberOfcards);
void printTessere(tessera* a, int size);
tessera* giveTessereToPlayer(tessera* tessere, int nTessere);
int chooseCard(tessera* playercards, int* numberOfcards);
void rotate(tessera* playerCards1, int i);
void pushHead(tessera* table, tessera* playerCards1, int choice, int* pointer);
void pushFooter(tessera* table, int size, tessera* playerCards1, int choice, int* pointer);

tessera* newPlayercards(tessera* playercards, int size, int choice);
int playMode();
void mod1(tessera* std, int numberOfcards);
void mossa(tessera* table, tessera* playerCards1, int* indexTable, int* numberOfcards, int* choiceptr, int mossa1, int tableSize);

int endPoints(tessera* table, int sizeTab);
void printDebug(char* message);
#endif // !DOMINO_H