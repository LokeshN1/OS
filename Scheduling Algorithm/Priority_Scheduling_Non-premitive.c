#include <stdio.h>
#include <stdlib.h>

// Prioirty Scheduling -> lower the no. higher the priority -> means process with priority 2 have higher prioirty then process with prioirty > 2

// Define the structure for a Process
typedef struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int ct;          // Completion Time
    int wt;          // Waiting Time
    int tat;         // Turnaround Time
    int st;          // Start Time
    int isCompleted; // Completion Status (1: Completed, 0: Not Completed)
    int priority;    // Priority of the process
} Process;

// Function to sort processes based on Arrival Time
void sortByArrival(Process *p, int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Function to find the next process to execute based on priority
int findNextProcess(Process *p, int n, int curtime) {
    int idx = -1;
    int highestPriority = 10000; // Initialize to an invalid priority

    for (int i = 0; i < n; i++) {
        // Check if the process has arrived and is not completed
        if (p[i].at <= curtime && p[i].isCompleted == 0) {
            // Check if the current process has a higher priority
            if (p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                idx = i; // Store the index of the process with the highest priority
            }
        }
    }
    return idx;
}

int main() {
    int n;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Allocate memory for processes
    Process *p = (Process *)malloc(n * sizeof(Process));

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].id = i + 1;
        p[i].isCompleted = 0; // Initialize as not completed
    }

    // Sort processes by arrival time
    sortByArrival(p, n);

    int completed = 0;   // Track the number of completed processes
    int curtime = 0;     // Current time

    // Execute processes until all are completed
    while (completed < n) {
        int idx = findNextProcess(p, n, curtime); // Get the index of the next process to execute

        if (idx != -1) {
            // Calculate timings for the selected process
            p[idx].st = curtime;                     // Start time
            p[idx].ct = curtime + p[idx].bt;        // Completion time
            p[idx].wt = p[idx].st - p[idx].at;      // Waiting time
            p[idx].tat = p[idx].ct - p[idx].at;     // Turnaround time
            p[idx].isCompleted = 1;                  // Mark as completed
            curtime += p[idx].bt;                    // Update current time
            completed++;                             // Increment completed count
        } else {
            curtime++; // Increment time if no process is ready
        }
    }

    // Display process information
    printf("\nProcess\tAT\tBT\tST\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].wt, p[i].tat);
    }

    // Free the dynamically allocated memory
    free(p);
    
    return 0;
}
