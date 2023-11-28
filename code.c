#include <stdio.h>

#define P 4 // Number of processes
#define R 16 // Number of resource types

int available[R];
int max[P][R];
int need[P][R];
int allocation[P][R];
int safeSequence[P];

void initialize() {
    // Define the maximum needs and current allocation for each process
    int i, j;

    for (i = 0; i < P; i++) {
        safeSequence[i] = -1;
        for (j = 0; j < R; j++) {
            max[i][j] = 0; // Define the maximum needs here
            allocation[i][j] = 0; // Define the current allocation here
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Define the available resources
    for (i = 0; i < R; i++) {
        available[i] = 0; // Define the available resources here
    }
}

int findSafeSequence() {
    int work[R];
    int finish[P];
    int i, j;
    
    for (i = 0; i < R; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < P; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < P) {
        int found = 0;
        for (i = 0; i < P; i++) {
            if (finish[i] == 0) {
                int canAllocate = 1;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) {
            // No safe sequence found
            return 0;
        }
    }
    return 1; // Safe sequence found
}

int main() {
    initialize();

    if (findSafeSequence()) {
        printf("Safe sequence: ");
        for (int i = 0; i < P; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("No safe sequence exists.\n");
    }

    return 0;
}