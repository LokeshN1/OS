#include <stdio.h>
#include <stdlib.h>

// Define structure for Process
typedef struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int rt;          // Remaining Time (for preemption)
    int ct;          // Completion Time
    int wt;          // Waiting Time
    int tat;         // Turnaround Time
    int isCompleted; // Completion status (1 if completed, 0 otherwise)
    int priority;    // Process Priority
} Process;

// Function to sort the processes based on arrival time
void sortByArrival(Process *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                // Swap the processes
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the processes
    Process *p = (Process *)malloc(n * sizeof(Process));

    // Input arrival time, burst time, and priority for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].id = i + 1;
        p[i].rt = p[i].bt;       // Initialize remaining time as burst time
        p[i].isCompleted = 0;    // Mark process as not completed
    }

    // Sort processes by arrival time
    sortByArrival(p, n);

    int completed = 0, curtime = 0, prev = -1;
    int totalWT = 0, totalTAT = 0;

    // Main loop to schedule processes based on priority
    while (completed < n) {
        int idx = -1;
        int maxPriority = 100000; // A large number to find the minimum priority

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= curtime && p[i].isCompleted == 0 && p[i].priority < maxPriority) {
                maxPriority = p[i].priority;
                idx = i;
            }
        }

        // If a process is found to run
        if (idx != -1) {
            if (prev != idx) {
                printf("Process %d started at time %d\n", p[idx].id, curtime);
            }

            // Execute process for one time unit
            p[idx].rt--;
            curtime++;

            // If process is completed
            if (p[idx].rt == 0) {
                p[idx].ct = curtime;                 // Completion time
                p[idx].tat = p[idx].ct - p[idx].at;  // Turnaround time
                p[idx].wt = p[idx].tat - p[idx].bt;  // Waiting time
                p[idx].isCompleted = 1;              // Mark process as completed

                // Update total waiting and turnaround times
                completed++;
                totalWT += p[idx].wt;
                totalTAT += p[idx].tat;

                printf("Process %d completed at time %d\n", p[idx].id, curtime);
            }

            // Update previous process
            prev = idx;
        } else {
            // Increment time if no process is ready
            curtime++;
        }
    }

    // Display process details
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Display average turnaround and waiting times
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);

    // Free allocated memory
    free(p);

    return 0;
}
