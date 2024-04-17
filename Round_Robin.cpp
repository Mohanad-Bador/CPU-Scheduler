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
    Process temp = list[0];
    for (size_t i = 0; i < list.size() - 1; i++) {
        list[i] = list[i + 1];
    }
    list[list.size() - 1] = temp;
}



vector<int> RR(int timequantum, vector<Process> &Waiting_queue) {
    vector<Process> Ready_queue;
    int n = Waiting_queue.size();
    int time = 0;
    int arrived_processes = 0;
    int finished_processes = 0;
    int ready_processes = 0;
    int q = timequantum;

    while (finished_processes < n) {
        int num_removed = 0; // Number of elements removed from Waiting_queue
        for (int i = 0; i < Waiting_queue.size(); i++) {
            if (time >= Waiting_queue[i].arrival_time) {
                Ready_queue.push_back(Waiting_queue[i]);
                arrived_processes++;
                ready_processes++;
                num_removed++;
            }
        }
        if(arrived_processes>1){
            Circular_Shift_Left(Ready_queue);
        }

        // Remove elements from Waiting_queue
        Waiting_queue.erase(Waiting_queue.begin(), Waiting_queue.begin() + num_removed);

        if (ready_processes ==0) {
            time++;
            continue;
        }

        if (Ready_queue[0].burst_time > 0) {
            if(Ready_queue[0].burst_time > q) {
                chart.push_back(Ready_queue[0].pid);
                    Ready_queue[0].burst_time -= q;
                    time+=q;

            }
            else {
                    chart.push_back(Ready_queue[0].pid);
                    time += Ready_queue[0].burst_time;
                    Ready_queue[0].burst_time = 0;
                    Ready_queue[0].finish_time = time;
                    finished_processes++;
                    ready_processes--;
            }
        }
    }

    return chart;
}


int main() {

    vector<Process>processes;
    // Initialize an empty vector of processes
    Process p1={1,0,5};
    Process p2={2,1,3};
    Process p3={3,3,6};
    Process p4={4,5,1};
    Process p5={5,6,4};
    processes.push_back(p1);
    processes.push_back(p2);
    processes.push_back(p3);
    processes.push_back(p4);
    processes.push_back(p5);
    int timeQuantum = 3;
    vector<int> Result = RR(timeQuantum, processes);

    cout << "Gantt Chart: ";
    for (int i = 0; i < Result.size(); i++) {
        cout << Result[i] << " | ";
    }

    return 0;
}




