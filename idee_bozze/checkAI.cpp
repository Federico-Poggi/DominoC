// Funzioni controllo IA

freq totalFreq[];

freq* getFreq() {
    return totalFreq;
}

// * Table contiene le tessere del tavolo
//* funzioni per riordinare un array temporaneo 
void sortMerge(tessera tempTable[], int left, int right) {

    if (left < right) {
        int middle = (left + right) / 2;
        sortMerge(tempTable, left, middle);
        sortMerge(tempTable, middle + 1, right);
        merge(tempTable, left, right, middle);
    }

}

void merge(tessera tempTable[], int left, int right, int middle) {
    int i;
    int j;
    int k;

    int sizeSub1 = middle - left + 1;
    int sizeSub2 = right - middle;
    //* creo due sottoarray con gli elemernti di destra e sinistra
    tessera sub1[sizeSub1];
    tessera sub2[sizeSub2];

    //* riempio gli array con gli elementi
    for (size_t i = 0; i < sizeSub1; i++)
    {
        sub1[i] = tempTable[left + i];
    }

    for (size_t j = 0; j < sizeSub2; j++)
    {
        sub2[j] = tempTable[middle + 1 + j];
    }

    //* REinizializzo l'indice del primo sub Array
    i = 0;
    //* REinizializzo l'indice del secondo sub Array
    j = 0;

    //*L'indice dell'array unito
    k = left;

    while (i < sizeSub1 && j < sizeSub2) {
        if (sub1[i].num1 >= sub2[j].num1) {
            tempTable[k] = sub1[i];
            i++;
        }
        else {
            tempTable[k] = sub2[j];
            j++;
        }
        k++;
    }

    //* copiare le tessere rimanenti se prersenti dentro sub1 o sub2

    while (i < sizeSub1)
    {
        tempTable[k] = sub1[i];
        i++;
        k++;
    }
    while (j < sizeSub2)
    {
        tempTable[k] = sub2[j];
        j++;
        k++;
    }

}

void updateFreq(freq* freqTot, int num, int frequency) {
    for (size_t i = 0; i < 6; i++)
    {
        if (freqTot[i].num == num && freqTot[i].frequency <= frequency) {
            freqTot[i].frequency = frequency;
            break;
        }
    }

}

void sumFreq(freq* freqTot1, freq* freqTot2) {
    for (size_t i = 0; i < 6; i++)
    {
        freqTot1[i].frequency += freqTot2[i].frequency;
    }
}

void printFreq(freq* freqTot) {
    for (size_t i = 0; i < 6; i++)
    {
        printf("Numero: %d\n", freqTot[i].num);
        printf("frequ: %d\n", freqTot[i].frequency);
    }
}

int findMostFrequent(tessera* table, int tableSize) {
    tessera* tempTable = malloc(tableSize * sizeof(tessera));
    int mostFreq;
    if (tempTable == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(tempTable, table, tableSize * sizeof(table));

    int leftIndex = 0;
    int rightIndex = tableSize - 1;

    sortMerge(tempTable, leftIndex, rightIndex);

    //*Array con frequenze;
    //** Frequenze num1
    freq freq_tot[6] = {
           {1,0},
           {2,0},
           {3,0},
           {4,0},
           {5,0},
           {6,0}
    };

    //**frequenze num2
    freq freq_tot_num2[6] = {
            {1,0},
            {2,0},
            {3,0},
            {4,0},
            {5,0},
            {6,0}
    };

    freq* ptr = freq_tot;
    freq* ptr2 = freq_tot_num2;

    //* frequNum1
    for (size_t i = 0; i < tableSize; i++)
    {
        int num1 = tempTable[i].num1;
        int counter = 1;
        int k = i + 1;
        while (k < tableSize && tempTable[k].num1 == num1)
        {
            counter++;
            k++;
        }
        updateFreq(ptr, num1, counter);
    }

    for (size_t i = 0; i < tableSize; i++)
    {
        rotate(tempTable, i);
    }

    sortMerge(tempTable, leftIndex, rightIndex);

    //*frequenze num1(num2);
    for (size_t i = 0; i < tableSize; i++)
    {
        int num1 = tempTable[i].num1;
        int counter2 = 1;
        int k = i + 1;
        while (k < tableSize && tempTable[k].num1 == num1)
        {
            counter2++;
            k++;
        }
        updateFreq(ptr2, num1, counter2);
    }

    sumFreq(ptr, ptr2);
    // printFreq(ptr);

    for (size_t i = 0; i < 6; i++)
    {
        if (mostFreq < ptr[i].frequency) {
            mostFreq = ptr[i].num;
        }
    }

    for (size_t i = 0; i < 6; i++)
    {
        totalFreq[i] = freq_tot[i];
    }



    free(tempTable);
    return mostFreq;
}

int unit_frequence(int num, freq* frequency) {
    for (size_t i = 0; i < 6; i++)
    {
        if (num == frequency[i].num) {
            return frequency[i].frequency;
        }
    }
    return 0;
}



// .h

typedef struct {
    int num;
    int frequency;
} freq;

typedef struct
{
    tessera card;
    int freq;
} cardObj; // ogetto carta che contiene tessera e sua frequenza

freq* getFreq();

int findMostFrequent(tessera* table, int tableSize);

// * funzioni di servizio per ordinare l'array in maniera decrescente num1
void merge(tessera tempTable[], int left, int right, int middle);
void sortMerge(tessera tempTable[], int left, int right);

//* Funzione che dato un numero ti ritorna la frequenza di quel numero;
int unit_frequence(int num, freq* frequency);