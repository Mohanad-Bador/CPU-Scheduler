#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Process {
public:
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int priority;

    Process(char pid, int AT, int BT) : pid(pid), arrival_time(AT), burst_time(BT), priority(0) {}

    int Waiting_Time() {
        return finish_time - arrival_time - burst_time;
    }

    int Turnaround_Time() {
        return finish_time - arrival_time;
    }
};


vector<int> chart ; // Gantt chart should be a vector of integers

void Circular_Shift_Left(vector<Process>&list) {
    int temp = list[0].pid;
    for (size_t i = 0; i < list.size() - 1; i++) {
        list[i].pid = list[i + 1].pid;
    }
    list[list.size() - 1].pid = temp;
}



vector<int> RR(int timequantum, vector<Process> &Waiting_queue) {
    vector<Process> Ready_queue;
    int n = Waiting_queue.size();
    int time = 0;
    int arrived_processes = 0;
    int finished_processes = 0;
    int ready_processes = 0;
    int q = timequantum;
    bool start = false;

    while (finished_processes < n) {
        for (int i = arrived_processes; i < n; i++) {
            if (time >= Waiting_queue[i].arrival_time) {
                Ready_queue.push_back(Waiting_queue[i]);
                arrived_processes++;
                ready_processes++;
            }
        }

        if (ready_processes < 1) {
            time++;
            continue;
        }

        if (start == true) {
            Circular_Shift_Left(Ready_queue);
        }

 //Errorrrrrrrrrr infinite loop

        if (Ready_queue[0].burst_time > 0) {
            if (Ready_queue[0].burst_time > q) {
                int number_of_iteration=Ready_queue[0].burst_time/q;
                for (int g = time; g < ceil(number_of_iteration); g++) {
                    chart.push_back(Ready_queue[0].pid);
                    Ready_queue[0].burst_time -= q;
                    time+=q;
                    Waiting_queue.push_back(Ready_queue[0]);
                    break;
                }
                start = true;
            } else {
                for (int g = time; g < time + Ready_queue[0].burst_time; g++) {
                    chart.push_back(Ready_queue[0].pid);
                    time += Ready_queue[0].burst_time;
                    Ready_queue[0].burst_time = 0;
                    Ready_queue[0].finish_time = time;
                    finished_processes++;
                    ready_processes--;
                    start = true;
                }
            }
        }





    }

//    while (finished_processes < n) {
//        bool found = false;
//        for (int i = 0; i < n; i++) {
//            if (time >= Waiting_queue[i].arrival_time) {
//                Ready_queue.push_back(Waiting_queue[i]);
//                Waiting_queue.erase(Waiting_queue.begin() + i); // Remove process from waiting queue
//                found = true;
//                break; // Exit the loop after finding a process to add to the ready queue
//            }
//        }
//
//        if (!found) {
//            time++;
//            continue;
//        }
//
//        if (Ready_queue[0].burst_time > 0) {
//            if (Ready_queue[0].burst_time > q) {
//                for (int g = 0; g < q; g++) {
//                    chart.push_back(Ready_queue[0].pid);
//                    Ready_queue[0].burst_time--;
//                    time++; // Increment time for each unit of burst time processed
//                }
//            } else {
//                int remaining_burst_time = Ready_queue[0].burst_time;
//                for (int g = 0; g < remaining_burst_time; g++) {
//                    chart.push_back(Ready_queue[0].pid);
//                    Ready_queue[0].burst_time = 0;
//                    Ready_queue[0].finish_time = time + 1;
//                    time++; // Increment time for each unit of burst time processed
//                    finished_processes++;
//                    ready_processes--;
//                    start = true;
//                }
//            }
//        }
//
//        Ready_queue.erase(Ready_queue.begin()); // Remove the processed process from the ready queue
//    }


    return chart;
}


int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    vector<Process> processes;  // Initialize an empty vector of processes

    for (int i = 0; i < num_processes; i++) {
        int pid, arrival_time, burst_time;
        cout << "Enter Process ID for Process " << i + 1 << ": ";
        cin >> pid;

        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> arrival_time;

        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> burst_time;

        processes.emplace_back(pid, arrival_time, burst_time);  // Add a new process to the vector

        // Debug output to verify process details
        cout << "Process " << i + 1 << " details: PID=" << processes[i].pid
             << ", Arrival Time=" << processes[i].arrival_time
             << ", Burst Time=" << processes[i].burst_time << endl;
    }

    int timeQuantum = 2;

    vector<int> Result = RR(timeQuantum, processes);

    cout << "Gantt Chart: ";
    for (int i = 0; i < Result.size(); i++) {
        cout << Result[i] << " | ";
    }

    return 0;
}




