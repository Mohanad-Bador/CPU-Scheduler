#include <bits/stdc++.h>  // Standard library header
#include <vector>          // Header for vectors
#include <thread>
#include <chrono>

using namespace std;

// Definition of the Process struct
struct Process {
    int id = -1;            // Default value -1 relate to empty process
    int burst_time = -1;
    int arrival_time = -1;
} typedef process;

process p_empty;
vector<process> input_Processes;  // Vector to store input input_Processes
vector<int> bursts;                                                                                      // Vector to store burst times of processes
int total_Burst_Time = 0;                                                                               // Total burst time of all processes

// Function to simulate Shortest Job First (SJF) scheduling algorithm
void SJF(vector<process> &processes, float &average_Waiting, float &average_Turnaround) {
    for (auto &process : processes) {
        bursts.push_back(process.burst_time);
        total_Burst_Time += process.burst_time;                                                         // Update total burst time
    }

    vector<process> output_Processes;                                                                   // Vector to store processes scheduled by SJF

    cout << "\nShortest Job First (Preemptive) scheduler:\n";
    int currentTime = 0;                                                                                // Current time during simulation
    // Simulate SJF scheduling
    while (currentTime < total_Burst_Time) {
        int min_burst = INT_MAX;                                                                        // Initialize minimum burst time to maximum integer value
        int chosen_process = -1;                                                                        // Initialize index of chosen process to -1

        // Find the process with the shortest remaining burst time
        for (int j = 0; j < processes.size(); ++j) {
            if (processes[j].arrival_time <= currentTime && bursts[j] > 0) {
                if (bursts[j] < min_burst) {
                    min_burst = bursts[j];
                    chosen_process = j;
                }
            }
        }
        // If a process is found to execute, schedule it
        if (chosen_process != -1) {
            while(bursts[chosen_process]--){
                output_Processes.push_back(processes[chosen_process]);
                cout << "P" << processes[chosen_process].id << "  ";
                this_thread::sleep_for(chrono::seconds(1));
                currentTime++;                                                                           // Increment current time
            }
        } else {
            output_Processes.push_back(p_empty);                                                        // Push empty process as there is no process ready to enter CPU at this time (bad CPU Utilization)
            currentTime++;
            total_Burst_Time++;                                                                         // Increment total burst time (to handle idle CPU time)
        }
    }

    int total_Waiting = 0;                                                                             // Total waiting time of all processes
    int total_Turnaround = 0;                                                                          // Total turnaround time of all processes

    // Calculate waiting time and turnaround time for each process
    for (auto &process : processes) {
        int finish;  // Finish time of the process

        // Find the finish time of the process in the SJF schedule
        for (int i = 0; i < output_Processes.size(); i++) {
            if (output_Processes[i].id == process.id) {
                finish = i + 1;
            }
        }
        // Update total waiting time and turnaround time
        total_Waiting += (finish - process.arrival_time - process.burst_time);
        total_Turnaround += (finish - process.arrival_time);
    }
    // Calculate average waiting time and average turnaround time
    average_Turnaround = (float) total_Turnaround / processes.size();
    average_Waiting = (float) total_Waiting / processes.size();
   // return output_Processes;  // Return the SJF schedule
}

void insert_Process (int burst_Time, int arrival_Time){
    this_thread::sleep_for(chrono::seconds(2));
    process p;
    p.id = input_Processes.size() + 1;
    p.burst_time = burst_Time;
    total_Burst_Time += burst_Time;
    p.arrival_time = arrival_Time;
    input_Processes.push_back(p);
    bursts.push_back(burst_Time);
}

int main() {
    int n;
    cout << "Enter number of input_Processes: \n";
    cin >> n;

    // Input burst time and arrival time for each process
    for (int i = 1; i <= n; ++i) {
        process p;
        p.id = input_Processes.size() + 1;

        cout << "Enter Burst Time of process " << i << ": \n";
        cin >> p.burst_time;

        cout << "Enter Arrival Time of process " << i << ": \n";
        cin >> p.arrival_time;

        input_Processes.push_back(p);                                                                          // Add the process to the vector of input_Processes
    }


    float average_Waiting = 0, average_Turnaround = 0;                                                        // Variables to store average waiting and turnaround times
    // Create thread for task 1
    thread t1([&]() { SJF(input_Processes, average_Waiting, average_Turnaround); });

    // Create thread for inserting process
    thread t2(insert_Process, 5, 0);

    // Join threads with main thread
    t1.join();
    t2.join();

    // Output average waiting time and average turnaround time
    cout << "\n\nAverage Waiting Time = " << average_Waiting << "\nAverage Turnaround Time = "
         << average_Turnaround << "\n\n";
}