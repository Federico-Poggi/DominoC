#include "ai.h"
#include <stdio.h>
#include <stdbool.h>

/**
 *
 * @brief **The Swap function, swap tile in AI-Hand inside Sort Function**
 *
 * @param AiCards1 *Tile 1 to swap*
 * @param AiCards2 *Tile 2 to swap*
 *
 * <center>
 * \code{c}
 * //*Function code
 * void swap(tessera* AiCards1, tessera* AiCards2) {
    tessera temp1 = *AiCards1;
    *AiCards1 = *AiCards2;
    *AiCards2 = temp1;
}
 * \endcode
 * </center>
 */
void swap(tessera* AiCards1, tessera* AiCards2) {
    tessera temp1 = *AiCards1;
    *AiCards1 = *AiCards2;
    *AiCards2 = temp1;
}

/**
 * @brief
 *  **Reorder of Ai-Hand** using **Buble Sort algorthim**
 *
 * @param AiCards  *AiHand array plain of cards*
 * @param Size *AiHand array's size*
 * \n
 *
 * \code{c}
 * //*Function code
 * void sortCards(tessera* AiCards, int Size) {
    // Sort num1
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if (AiCards[j].num1 > AiCards[j + 1].num1) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }

    // Sort num2
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if ((AiCards[j].num1 == AiCards[j + 1].num1) && (AiCards[j].num2 > AiCards[j + 1].num2)) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }
}
 * \endcode
 *
 */
void sortCards(tessera* AiCards, int Size) {
    // Sort num1
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if (AiCards[j].num1 > AiCards[j + 1].num1) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }

    // Sort num2 
    for (int i = 0; i < Size - 1; i++) {
        for (int j = 0; j < Size - 1; j++) {
            if ((AiCards[j].num1 == AiCards[j + 1].num1) && (AiCards[j].num2 > AiCards[j + 1].num2)) {
                swap(&AiCards[j], &AiCards[j + 1]);
            }
        }
    }
}

/**
 * @brief
 *  **Keep tracks of the frequencies of the hand tiles**
 *
 * @param aiCards1  *Ai-hand with tiles*
 * @param freq  *Frequencies array*
 * @param numberOfCards *Current Ai-Hand size*
 */
void inizializza(tessera* aiCards1, int freq[], int numberOfCards) {
    int count; //Conteggio frequenza tessere 
    for (int i = 0; i < numberOfCards; ++i) {
        count = 0;
        for (int j = 0; j < numberOfCards; ++j) {
            if ((aiCards1[i].num1 == aiCards1[j].num1) && (aiCards1[i].num2 == aiCards1[j].num2)) {
                count++;
            }
        }
        freq[i] = count;
    }
}

/**
 * @brief **Search the most frequent tiles and return the index of the tile into Ai-Hand**
 *
 * @param aiCards1  *Ai-hand with tiles*
 * @param freq  *Frequencies array*
 * @param numberOfCards *Current Ai-Hand size*
 * @return int (Index)
 *
 *
 * \code{c}
 *
 * int findfirst(tessera* aiCards1, int freq[], int numberOfcards) {
    int out = 0;
    int max = freq[0];
    for (int i = 1; i < numberOfcards; ++i) {
        if (freq[i] > max) {
            max = freq[i];
            out = i;
        }
        if (freq[i] == max) {
            if ((aiCards1[i].num1 + aiCards1[i].num2) > (aiCards1[out].num1 + aiCards1[out].num2)) {
                out = i;
            }
        }
    }
    printf("\ncard -> [%d|%d] _ freq -> %d\n", aiCards1[out].num1, aiCards1[out].num2, freq[out]);
    return out;
}
 * \endcode
 */
int findfirst(tessera* aiCards1, int freq[], int numberOfcards) {
    int out = 0;
    int max = freq[0];
    for (int i = 1; i < numberOfcards; ++i) {
        if (freq[i] > max) {
            max = freq[i];
            out = i;
        }
        if (freq[i] == max) {
            if ((aiCards1[i].num1 + aiCards1[i].num2) > (aiCards1[out].num1 + aiCards1[out].num2)) {
                out = i;
            }
        }
    }
    return out;
}

/**
 * @brief **Given a number, that rappresent the number most right or most left of the current table, it will return the index of the tiles that can be insert at next move**
 *
 * @param aiCards1 *Ai-hand with tiles*
 * @param freq *Frequencies array*
 * @param tableSize
 * @param dx_sx *The most right number or most left number*
 * @return int (Index)
 *
 * \code{c}
 * int findDX_SX(tessera* aiCards1, int freq[], int tableSize, int dx_sx) {
    int out = 0;
    int max = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (aiCards1[i].num1 == dx_sx || aiCards1[i].num2 == dx_sx) {
            if (freq[i] > max) {
                max = freq[i];
                out = i;
            }
            if (freq[i] == max) {
                if ((aiCards1[i].num1 + aiCards1[i].num2) > (aiCards1[out].num1 + aiCards1[out].num2)) {
                    out = i;
                }
            }
        }
    }
    return out;
};
 * \endcode
 *
 */
int findDX_SX(tessera* aiCards1, int freq[], int tableSize, int dx_sx) {
    int out = 0;
    int max = 0;
    for (int i = 0; i < tableSize; ++i) {
        if (aiCards1[i].num1 == dx_sx || aiCards1[i].num2 == dx_sx) {
            // CARTA VALORI UGUALI
            if (aiCards1[i].num1 == aiCards1[i].num2) {
                max = freq[i];
                out = i;
                return out;
            }
            if (freq[i] > max) {
                max = freq[i];
                out = i;
            }
            if (freq[i] == max) {
                if ((aiCards1[i].num1 + aiCards1[i].num2) > (aiCards1[out].num1 + aiCards1[out].num2)) {
                    out = i;
                }
            }
        }
    }

    return out;
};

/**
 * @brief **Remove the chosen tiles and set it at [0|0], and put them at the end of the array**
 *
 * @param aiCards1 *Ai-hand with tiles*
 * @param index *Index of the chosen tile*
 * @param tablesize
 *
 * \code{c}
 *
 * void pop_back(tessera* aiCards1, int index, int tablesize) {
    tessera temp = aiCards1[index];
    for (size_t i = index; i < tablesize - 1; i++)
    {
        aiCards1[i] = aiCards1[i + 1];
    }
    aiCards1[tablesize - 1] = temp;
};
 *
 * \endcode
 */
void pop_back(tessera* aiCards1, int index, int tablesize) {
    tessera temp = aiCards1[index];
    for (size_t i = index; i < tablesize - 1; i++)
    {
        aiCards1[i] = aiCards1[i + 1];
    }
    aiCards1[tablesize - 1] = temp;
};

/**
 * @brief **This is a CHECK for control if have to pass to the left side of the table**
 *
 * @param AiCards *Ai-hand with tiles*
 * @param indexAi *Index of the chosen tile*
 * @param numTable *Most right or most left number of the current table*
 * @return **TRUE** *If the tile can be inserted at the current position*
 * @return **FALSE** *If the tile can't be inserted*
 *
 * \code{c}
 *
 * bool sohuldEnter(tessera* AiCards, int indexAi, int numTable) {
    return(AiCards[indexAi].num1 == numTable || AiCards[indexAi].num2 == numTable);
};
 * \endcode
 */
bool sohuldEnter(tessera* AiCards, int indexAi, int numTable) {
    return(AiCards[indexAi].num1 == numTable || AiCards[indexAi].num2 == numTable);
};
