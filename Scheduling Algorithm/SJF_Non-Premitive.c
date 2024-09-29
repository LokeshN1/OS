#include <stdio.h>
#include <stdlib.h>

// Define the structure for a Process
typedef struct Process {
    int id;
    int at; // Arrival time
    int bt; // Burst time
    int ct; // Completion time
    int wt; // Waiting time
    int tat; // Turnaround time
    int st; // Start time
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

// Function to find the next process to execute (based on SJF criteria)
int findNextProcess(P *p, int n, int curtime) {
    int burstT = 100000, idx = -1; // Initially set burstT to a very high value
    for (int i = 0; i < n; i++) {
        if (p[i].at <= curtime && p[i].isCompleted == 0) { // Check if process has arrived and is not completed
            if (p[i].bt < burstT) {
                burstT = p[i].bt;
                idx = i;
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
    P *p = (P *)malloc(n * sizeof(P));

    // Input arrival and burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].isCompleted = 0; // Initialize completion status as 0 (not completed)
    }

    // Sort the processes by arrival time
    sortByArrival(p, n);

    int completed = 0;   // Track the number of completed processes
    int curtime = 0;     // Current time

    // Main loop to execute all processes
    while (completed < n) {
        int idx = findNextProcess(p, n, curtime); // Get the index of the next process to execute

        if (idx != -1) 
        {
            p[idx].st = curtime;                     // Set the start time of the process
            p[idx].ct = curtime + p[idx].bt;         // Calculate completion time
            p[idx].wt = p[idx].st - p[idx].at;       // Calculate waiting time
            p[idx].tat = p[idx].ct - p[idx].at;      // Calculate turnaround time
            p[idx].isCompleted = 1;                  // Mark process as completed
            curtime += p[idx].bt;                    // Update current time
            completed++;                             // Increment the count of completed processes
        } else {
            curtime++; // Increment current time if no process is ready
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
