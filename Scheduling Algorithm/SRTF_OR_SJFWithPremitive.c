#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int at; // Arrival time
    int bt; // Burst time
    int rt; // Remaining time (for preemption)
    int ct; // Completion time
    int wt; // Waiting time
    int tat; // Turnaround time
    int isCompleted; // 1 if completed, 0 otherwise
} P;

// Function to sort the processes based on arrival time
void sortByArrival(P *p, int n) {
    P temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    P *p = (P *)malloc(n * sizeof(P)); // Dynamically allocate memory for processes

    // Input arrival time and burst time
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].rt = p[i].bt; // Initialize remaining time as burst time
        p[i].isCompleted = 0; // Mark as not completed
    }
    sortByArrival(p, n);

    int completed = 0, curtime = 0, prev = -1;
    int totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1, minRT = 100000;

        // Find the process with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= curtime && p[i].isCompleted == 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                idx = i;
            }
        }

        // If a process is found to run
        if (idx != -1) {
            if (prev != idx) {
                printf("Process %d started at time %d\n", p[idx].id, curtime);
            }

            // Process is executed for one unit of time
            p[idx].rt--;
            curtime++;

            // If the process is completed
            if (p[idx].rt == 0) {
                p[idx].ct = curtime; // Completion time is current time
                p[idx].tat = p[idx].ct - p[idx].at; // Turnaround time
                p[idx].wt = p[idx].tat - p[idx].bt; // Waiting time
                p[idx].isCompleted = 1; // Mark the process as completed

                completed++; // Increment the number of completed processes
                totalWT += p[idx].wt; // Add to total waiting time
                totalTAT += p[idx].tat; // Add to total turnaround time

                printf("Process %d completed at time %d\n", p[idx].id, curtime);
            }

            prev = idx; // Keep track of the current running process
        } else {
            // If no process is ready, increment time
            curtime++;
        }
    }

    // Display the results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);
    printf("Average Waiting Time: %.2f\n", (float)totalWT / n);

    free(p); // Free allocated memory

    return 0;
}
