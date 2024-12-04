#include <stdio.h>

// Define a structure to represent a process
struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int completionTime; // Completion time
    int waitingTime;    // Waiting time
    int turnaroundTime; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime; // Wait for the process to arrive
        }

        // Calculate completion time
        processes[i].completionTime = currentTime + processes[i].burstTime;
        currentTime = processes[i].completionTime;

        // Calculate turnaround time and waiting time
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
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
    }

    // Sort processes by arrival time (FCFS requires this)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion, turnaround, and waiting times
    calculateTimes(processes, n);

    // Print the process table
    printTable(processes, n);

    return 0;
}
