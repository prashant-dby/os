#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes, int resources, int available[], int max[MAX_PROCESSES][MAX_RESOURCES],
            int allocation[MAX_PROCESSES][MAX_RESOURCES]) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, processes, resources);

    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < processes) {
        bool found = false;

        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canAllocate = true;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    
    isSafe(processes, resources, available, max, allocation);

    return 0;
}
