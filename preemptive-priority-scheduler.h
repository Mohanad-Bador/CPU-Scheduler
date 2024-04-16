#ifndef PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
#define PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED

#include <algorithm>
#include "process.h"
#include "priorityQ.h"

void P_Priority(vector<process> &inQ , int &current_time){
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
            process P = Q.extractMin();
            if(P.getBurstTime()>0){
            cout << "Current Time: " << current_time << endl;
            cout << "Executing Process ID: " << P.getPid() << endl;
                P.setBurstTime(P.getBurstTime()-1);
                Q.insert(P);
            current_time++;
            }
        }
    }
    while(inQ.empty()&&!Q.isEmpty()){
            process P = Q.extractMin();
            if(P.getBurstTime()>0){
            cout << "Current Time: " << current_time << endl;
            cout << "Executing Process ID: " << P.getPid() << endl;
                P.setBurstTime(P.getBurstTime()-1);
                current_time++;
                Q.insert(P);
            }
    }

}

#endif // PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
