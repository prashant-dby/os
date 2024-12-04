#include <stdio.h>
#include <limits.h>

struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int remainingTime;  // Remaining time
    int completionTime; // Completion time
    int waitingTime;    // Waiting time
    int turnaroundTime; // Turnaround time
    int isCompleted;    // Completion status
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;
    int minIndex;
    int minRemainingTime;

    while (completed < n) {
        minIndex = -1;
        minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime &&
                !processes[i].isCompleted &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            // No process is ready; increment the time
            currentTime++;
        } else {
            // Execute the process for 1 unit of time
            processes[minIndex].remainingTime--;
            currentTime++;

            // Check if the process is completed
            if (processes[minIndex].remainingTime == 0) {
                processes[minIndex].completionTime = currentTime;
                processes[minIndex].turnaroundTime = 
                    processes[minIndex].completionTime - processes[minIndex].arrivalTime;
                processes[minIndex].waitingTime = 
                    processes[minIndex].turnaroundTime - processes[minIndex].burstTime;
                processes[minIndex].isCompleted = 1;
                completed++;
            }
        }
    }
}

void printTable(struct Process processes[], int n) {
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Assign process ID
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
        processes[i].isCompleted = 0; // Mark process as incomplete
    }

    // Calculate completion, turnaround, and waiting times
    calculateTimes(processes, n);

    // Print the process table
    printTable(processes, n);

    return 0;
}
