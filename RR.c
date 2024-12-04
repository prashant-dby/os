#include <stdio.h>
#include <stdbool.h>

// Define a structure to represent a process
struct Process {
    int id;                 // Process ID
    int arrivalTime;        // Arrival time
    int burstTime;          // Burst time
    int remainingTime;      // Remaining burst time
    int completionTime;     // Completion time
    int turnaroundTime;     // Turnaround time
    int waitingTime;        // Waiting time
};

// Function to calculate completion, turnaround, and waiting times
void calculateTimes(struct Process processes[], int n, int quantum) {
    int currentTime = 0;      // Current time
    int completed = 0;        // Number of processes completed
    bool isCompleted[n];     // Array to track completed processes

    // Initialize remaining time and completion status
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        isCompleted[i] = false;
    }

    while (completed != n) {
        bool flag = false; // Flag to check if any process is executed in this cycle

        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and is not completed
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i]) {
                flag = true; // At least one process is ready

                if (processes[i].remainingTime > quantum) {
                    // Execute the process for quantum time
                    currentTime += quantum;
                    processes[i].remainingTime -= quantum;
                } else {
                    // Execute the process for its remaining time
                    currentTime += processes[i].remainingTime;
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    processes[i].remainingTime = 0;
                    isCompleted[i] = true;
                    completed++;
                }
            }
        }

        // If no process was executed in this cycle, increment time
        if (!flag) {
            currentTime++;
        }
    }
}

// Function to print the process table
void printTable(struct Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
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

// Function to calculate average turnaround and waiting times
void calculateAverages(struct Process processes[], int n, float *avgTurnaround, float *avgWaiting) {
    *avgTurnaround = 0;
    *avgWaiting = 0;
    for (int i = 0; i < n; i++) {
        *avgTurnaround += processes[i].turnaroundTime;
        *avgWaiting += processes[i].waitingTime;
    }
    *avgTurnaround /= n;
    *avgWaiting /= n;
}

int main() {
    int n, quantum;

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

    // Input time quantum
    printf("Enter the Time Quantum: ");
    scanf("%d", &quantum);

    // Calculate times
    calculateTimes(processes, n, quantum);

    // Print the process table
    printTable(processes, n);

    // Calculate and print average turnaround and waiting times
    float avgTurnaround, avgWaiting;
    calculateAverages(processes, n, &avgTurnaround, &avgWaiting);
    printf("\nAverage Turnaround Time: %.2f", avgTurnaround);
    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);

    return 0;
}
