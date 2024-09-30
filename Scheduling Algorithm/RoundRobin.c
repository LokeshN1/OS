#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int ct;         // Completion Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
} Process;

int isEmpty(int front, int rear, int n) {
    return front == -1;  // Queue is empty when front is -1
}

int isFull(int front, int rear, int n) {
    return (rear + 1) % n == front;  // Queue is full in circular queue when rear + 1 == front
}

int main() {
    int n, tq, time = 0, completed = 0, front = -1, rear = -1;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    Process *p = (Process *)malloc(n * sizeof(Process));
    int *queue = (int *)malloc(n * sizeof(int));
    int *isInQueue = (int *)malloc(n * sizeof(int)); // Tracks if process is in queue

    // Initialize all processes
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].rt = p[i].bt; // Initialize remaining time as burst time
        isInQueue[i] = 0;   // Initially, no process is in the queue
    }

    // Enqueue process 0 if it has arrived at time 0
    if (p[0].at <= time) {
        front = rear = 0;
        queue[rear] = 0;
        isInQueue[0] = 1;
    }

    while (completed < n) {
        if (!isEmpty(front, rear, n)) {
            int idx = queue[front];     // Get the process index from the queue
            if (front == rear)          // If only one element in the queue, reset front and rear
                front = rear = -1;
            else                        // Otherwise, update front in circular manner
                front = (front + 1) % n;

            if (p[idx].rt > tq) {
                // Process doesn't finish within the time quantum
                p[idx].rt -= tq;
                time += tq;
            } else {
                // Process finishes within the time quantum
                time += p[idx].rt;
                p[idx].rt = 0;
                p[idx].ct = time;                    // Completion time
                p[idx].tat = p[idx].ct - p[idx].at;  // Turnaround time
                p[idx].wt = p[idx].tat - p[idx].bt;  // Waiting time
                completed++;                         // One more process completed
            }

            // Enqueue new processes that have arrived within the current time
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rt > 0 && !isInQueue[i]) {
                    if (!isFull(front, rear, n)) {    // Check if queue is full
                        rear = (rear + 1) % n;
                        queue[rear] = i;
                        isInQueue[i] = 1;
                        if (front == -1) front = rear; // First process in queue
                    }
                }
            }

            // Re-enqueue the current process if it's not finished
            if (p[idx].rt > 0) {
                if (!isFull(front, rear, n)) {        // Check if queue is full
                    rear = (rear + 1) % n;
                    queue[rear] = idx;
                    if (front == -1) front = rear;    // First process in queue
                }
            }
        } else {
            // If no processes are in the queue, increment time until one arrives
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && p[i].rt > 0 && !isInQueue[i]) {
                    if (!isFull(front, rear, n)) {    // Check if queue is full
                        rear = (rear + 1) % n;
                        queue[rear] = i;
                        isInQueue[i] = 1;
                        if (front == -1) front = rear; // First process in queue
                    }
                }
            }
        }
    }

    // Display the results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    free(p);
    free(queue);
    free(isInQueue);

return 0;
}
