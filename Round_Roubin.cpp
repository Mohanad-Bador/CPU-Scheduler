#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Process {
public:
    string pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int priority;

    Process(string p, int a, int b) : pid(p), arrival_time(a), burst_time(b), priority(0) {}

    int Waiting_Time() {
        return finish_time - arrival_time - burst_time;
    }

    int Turnaround_Time() {
        return finish_time - arrival_time;
    }
};

vector<int> chart = {0};

vector<Process> Circular_Shift_Left(const vector<Process>& list) {
    vector<Process> shiftedList = list;
    Process temp = shiftedList[0];
    for (size_t i = 0; i < shiftedList.size() - 1; i++) {
        shiftedList[i] = shiftedList[i + 1];
    }
    shiftedList[shiftedList.size() - 1] = temp;
    return shiftedList;
}

vector<Process> RR(int timequantum, vector<Process>& Waiting_queue) {
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
            Ready_queue = Circular_Shift_Left(Ready_queue);
        }

        if (Ready_queue[0].burst_time > 0) {
            if (Ready_queue[0].burst_time > q) {
                for (int g = time; g < time + q; g++) {       //*******
                    chart.push_back(stoi(Ready_queue[0].pid));
                    time += q;
                    Ready_queue[0].burst_time -= q;
                }

            } else {
                for (int g = time; g < time + Ready_queue[0].burst_time; g++) {
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

    return Waiting_queue; // Return Waiting_queue or Ready_queue?
}

int main() {
    vector<Process> processes = {
            {"1", 0, 5},
            {"2", 1, 4},
            {"3", 2, 2},
            {"4", 3, 1}
    };

    int timeQuantum = 2;

    RR(timeQuantum, processes);

    cout << "Gantt Chart: ";
    for (int process : chart) {
        cout << process << " ";
    }
    cout << endl;

    return 0;
}
