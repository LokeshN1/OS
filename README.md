# OS
FCFS -:
  sort by arrival time 
  then calculate their at, wt etc

SJF Non-Preemptive:

Sort by Arrival Time: Sort all processes based on their arrival time.
Find the Next Process: Use a function to select the process with the shortest burst time that has already arrived.
Track Completion: Use a variable (isCompleted) to keep track of completed processes.
Execute and Update Time: Execute processes and update the current time, start time, waiting time, and turnaround time for each process.

Steps for SRTF (Shortest Remaining Time First):
Input Arrival and Burst Times for all processes.
Sort Processes by Arrival Time initially, but the order of execution is determined dynamically.
Track the Remaining Burst Time of each process and update it during execution.
Preempt the current process if a new process with a shorter burst time arrives.
Calculate Completion Time (CT), Turnaround Time (TAT), and Waiting Time (WT) for each process.
Use a loop to simulate each time unit and decide which process to run at that time.
