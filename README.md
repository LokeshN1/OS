# OS
FCFS -:
  sort by arrival time 
  then calculate their at, wt etc

SJF Non-Preemptive:

Sort by Arrival Time: Sort all processes based on their arrival time.
Find the Next Process: Use a function to select the process with the shortest burst time that has already arrived.
Track Completion: Use a variable (isCompleted) to keep track of completed processes.
Execute and Update Time: Execute processes and update the current time, start time, waiting time, and turnaround time for each process.
