#include <iostream>
#include <vector>
#include"PROCESS.h"

vector<int> chart ; // Gantt chart should be a vector of integers

void Circular_Shift_Left(vector<process>&list) {
    process temp = list[0];
    for (size_t i = 0; i < list.size() - 1; i++) {
        list[i] = list[i + 1];
    }
    list[list.size() - 1] = temp;
}

vector<int> RR(int timequantum, vector<process> &Waiting_queue) {
    bool flag=false;
    vector<process> Ready_queue;
    int n = Waiting_queue.size();
    int time = 0;
    int arrived_processes = 0;
    int finished_processes = 0;
    int ready_processes = 0;
    int q = timequantum;

    while (finished_processes < n) {
        int num_removed = 0; // Number of elements removed from Waiting_queue
        for (int i = 0; i < Waiting_queue.size(); i++) {
            if (time >= Waiting_queue[i].at) {
                Ready_queue.push_back(Waiting_queue[i]);
                arrived_processes++;
                ready_processes++;
                num_removed++;
            }
        }
        if(arrived_processes>1&&flag){
            Circular_Shift_Left(Ready_queue);
        }

        // Remove elements from Waiting_queue
        Waiting_queue.erase(Waiting_queue.begin(), Waiting_queue.begin() + num_removed);

        if (ready_processes ==0) {
            time++;
            continue;
        }

        if (Ready_queue[0].bt > 0) {
            flag= true;
            if(Ready_queue[0].bt > q) {
                chart.push_back(Ready_queue[0].id);
                    Ready_queue[0].bt -= q;
                    time+=q;

            }
            else {
                    chart.push_back(Ready_queue[0].id);
                    time += Ready_queue[0].bt;
                    Ready_queue[0].bt = 0;
                    Ready_queue[0].ft = time;
                    finished_processes++;
                    ready_processes--;
            }
        }
    }

    return chart;
}





