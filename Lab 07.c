#include <stdio.h>
#include <stdbool.h>

#define PAGE_FRAMES 3
#define REFERENCE_LENGTH 20

// Função para verificar se uma página já está na memória
bool isPageInMemory(int page, int memory[]) {
    for (int i = 0; i < PAGE_FRAMES; i++) {
        if (memory[i] == page) {
            return true;
        }
    }
    return false;
}

// Algoritmo FIFO
int fifo(int referenceString[]) {
    int memory[PAGE_FRAMES] = {-1, -1, -1};
    int faults = 0;
    int index = 0;

    for (int i = 0; i < REFERENCE_LENGTH; i++) {
        if (!isPageInMemory(referenceString[i], memory)) {
            memory[index] = referenceString[i];
            index = (index + 1) % PAGE_FRAMES;
            faults++;
        }
    }

    return faults;
}

// Algoritmo LRU
int lru(int referenceString[]) {
    int memory[PAGE_FRAMES] = {-1, -1, -1};
    int lastUsed[PAGE_FRAMES] = {0};
    int faults = 0;

    for (int i = 0; i < REFERENCE_LENGTH; i++) {
        if (!isPageInMemory(referenceString[i], memory)) {
            int leastRecentlyUsed = 0;
            for (int j = 1; j < PAGE_FRAMES; j++) {
                if (lastUsed[j] < lastUsed[leastRecentlyUsed]) {
                    leastRecentlyUsed = j;
                }
            }
            memory[leastRecentlyUsed] = referenceString[i];
            faults++;
        }

        for (int j = 0; j < PAGE_FRAMES; j++) {
            if (memory[j] == referenceString[i]) {
                lastUsed[j] = i;
                break;
            }
        }
    }

    return faults;
}

// Algoritmo Ótimo
int optimal(int referenceString[]) {
    int memory[PAGE_FRAMES] = {-1, -1, -1};
    int faults = 0;

    for (int i = 0; i < REFERENCE_LENGTH; i++) {
        if (!isPageInMemory(referenceString[i], memory)) {
            int farthest = -1;
            int index = -1;
            for (int j = 0; j < PAGE_FRAMES; j++) {
                int k;
                for (k = i + 1; k < REFERENCE_LENGTH; k++) {
                    if (memory[j] == referenceString[k]) {
                        if (k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        break;
                    }
                }
                if (k == REFERENCE_LENGTH) {
                    index = j;
                    break;
                }
            }
            memory[index == -1 ? 0 : index] = referenceString[i];
            faults++;
        }
    }

    return faults;
}

int main() {
    int referenceString[REFERENCE_LENGTH] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};

    int fifoFaults = fifo(referenceString);
    int lruFaults = lru(referenceString);
    int optimalFaults = optimal(referenceString);

    printf("Faltas de página no FIFO: %d\n", fifoFaults);
    printf("Faltas de página no LRU: %d\n", lruFaults);
    printf("Faltas de página no Ótimo: %d\n", optimalFaults);

    return 0;
}
