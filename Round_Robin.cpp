#include <iostream>
#include <vector>
#include "PROCESS.h" // Include the header file for the 'process' class

using namespace std;

vector<int> chart; // Gantt chart should be a vector of integers

/*
 * This function is used to shift processes so that the process which has burst time greater than the time quantum
 * gets shifted to the end of the ready queue.
 */
void Circular_Shift_Left(vector<process>& list) {
    process temp = list[0]; // Store the first process temporarily
    for (size_t i = 0; i < list.size() - 1; i++) {
        list[i] = list[i + 1]; // Shift each process one position to the left
    }
    list[list.size() - 1] = temp; // Place the temporarily stored process at the end
}

/*
 * This function implements the Round Robin scheduling algorithm.
 * Parameters:
 * - timequantum: Time quantum for Round Robin scheduling
 * - Waiting_queue: Vector containing processes in the waiting queue
 * Returns:
 * - Gantt chart showing the sequence of execution
 */
vector<int> RR(int timequantum, vector<process>& Waiting_queue) {
    bool flag = false; // Flag to indicate if circular shift is needed
    vector<process> Ready_queue; // Queue containing processes ready for execution
    int n = Waiting_queue.size(); // Total number of processes
    int time = 0; // Current time
    int arrived_processes = 0; // Number of processes that have arrived
    int finished_processes = 0; // Number of processes that have finished execution
    int ready_processes = 0; // Number of processes ready for execution
    int q = timequantum; // Time quantum for Round Robin

    // Loop until all processes finish execution
    while (finished_processes < n) {
        int num_removed = 0; // Number of elements removed from Waiting_queue
        // Check for processes that have arrived and move them to the ready queue
        for (int i = 0; i < Waiting_queue.size(); i++) {
            if (time >= Waiting_queue[i].at) {
                Ready_queue.push_back(Waiting_queue[i]);
                arrived_processes++;
                ready_processes++;
                num_removed++;
            }
        }
        // If more than one process has arrived and circular shift has been performed, shift again
        if (arrived_processes > 1 && flag) {
            Circular_Shift_Left(Ready_queue);
        }

        // Remove elements from Waiting_queue
        Waiting_queue.erase(Waiting_queue.begin(), Waiting_queue.begin() + num_removed);

        // If no process is ready for execution, increment time and continue
        if (ready_processes == 0) {
            time++;
            continue;
        }

        // Execute processes in the ready queue using Round Robin scheduling
        if (Ready_queue[0].bt > 0) {
            flag = true; // Set flag to true indicating circular shift may be needed
            if (Ready_queue[0].bt > q) {
                chart.push_back(Ready_queue[0].id); // Add process ID to the Gantt chart
                Ready_queue[0].bt -= q; // Reduce remaining burst time by the time quantum
                time += q; // Increment time by the time quantum
            } else {
                chart.push_back(Ready_queue[0].id); // Add process ID to the Gantt chart
                time += Ready_queue[0].bt; // Increment time by the remaining burst time
                Ready_queue[0].bt = 0; // Set burst time of the process to 0 indicating completion
                Ready_queue[0].ft = time; // Set finish time of the process
                finished_processes++; // Increment the count of finished processes
                ready_processes--; // Decrement the count of processes ready for execution
            }
        }
    }

    return chart; // Return the Gantt chart
}
