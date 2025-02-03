# CPU Scheduler

This project simulates **CPU scheduling algorithms** with a user-friendly **GUI desktop application**. It supports multiple types of schedulers and provides real-time outputs such as **Gantt charts**, **average waiting time**, and **average turnaround time**.

## Features

- **Dynamic Process Addition**  
  Add new processes during the scheduler's runtime.
  
- **Live Scheduling**  
  Real-time scheduler with updates to **remaining burst times** and a live **Gantt chart** showing process execution.

- **Supported Schedulers**  
  - **FCFS (First-Come-First-Served)**
  - **SJF (Shortest Job First)** – Preemptive and Non-Preemptive
  - **Priority Scheduling** – Preemptive and Non-Preemptive (lower numbers indicate higher priority)
  - **Round Robin**

- **Process Info Input**  
  Prompts for necessary info based on selected scheduler type. (For example, no need to input priority for **FCFS**)

- **Non-Live Scheduling Option**  
  Run processes without live scheduling to calculate the results instantly.

- **Performance Metrics**  
  Calculates **average waiting time** and **average turnaround time**.

- **Real-Time Output**  
  - **Gantt Chart**  
  - **Remaining Burst Time Table**

## Usage

1. **Launch the Application**  
   Open the executable file and select a scheduler type.
   
2. **Input Process Information**  
   Enter process details such as burst time, priority, etc., based on the scheduler type.

3. **Start Scheduling**  
   Choose between live or non-live scheduling.

4. **View Results**  
   After execution, view the **Gantt chart** and calculated **average waiting time** and **turnaround time**.

## Installation

1. Choose latest release
2. run CPU_Sche.exe
3. Enter the number of processes you want to scheduler
4. Choose the algorithm to schedule by
5. Click Input
6. Enter the processes data
7. Click Load then Simulate

## Conclusion

This project demonstrates the implementation of CPU scheduling algorithms and provides an interactive GUI to visualize the scheduling process and calculate important system performance metrics.


## Document
[OS_Project.pdf](https://github.com/user-attachments/files/16039794/OS_Project.pdf)
