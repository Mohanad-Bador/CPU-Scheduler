#ifndef NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
#define NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED

#include <algorithm>
#include "process.h"
#include "priorityQ.h"

void NP_Priority(vector<process> &inQ , int &current_time){
    PriorityQueue Q;
    while(!inQ.empty()){
        for (auto it = inQ.begin(); it != inQ.end();) {
            const auto& process = *it;
            //cout << "inside for loop" << endl;
            if (process.getArrivalTime() <= current_time) {
                Q.insert(process);
                it = inQ.erase(it); // Erase and update iterator
                //cout << "inside if" << endl;
            } else {
                ++it; // Move to the next element
            }
        }
        if(Q.isEmpty()&&!inQ.empty())
            current_time++;
        if(!Q.isEmpty()){
            cout << "Current Time: " << current_time << endl;
            process P = Q.extractMin();
            cout << "Executing Process ID: " << P.getPid() << endl;
            current_time = current_time + P.getBurstTime();
        }
    }
    while(inQ.empty()&&!Q.isEmpty()){
        cout << "Current Time: " << current_time << endl;
        process P = Q.extractMin();
        cout << "Executing Process ID: " << P.getPid() << endl;
        current_time = current_time + P.getBurstTime();
    }

}

#endif // NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
