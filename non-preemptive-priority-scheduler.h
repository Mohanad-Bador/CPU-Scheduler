#ifndef NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
#define NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED

#include <algorithm>
#include "process.h"
#include "priorityQ.h"

void NP_Priority(vector<process> &inQ , int &current_time){
    PriorityQueue Q;
    vector<int> WaitingTime;
    vector<int> TurnAroundTime;
    cout<<"Gantt Chart For NP Priority Scheduler"<<endl;
    cout<<current_time<<' ';
    while(!inQ.empty()){
        for (auto it = inQ.begin(); it != inQ.end();) {
            const auto& process = *it;
            if (process.getArrivalTime() <= current_time) {
                Q.insert(process);
                it = inQ.erase(it); // Erase and update iterator
            } else {
                ++it; // Move to the next element
            }
        }
        if(Q.isEmpty()&&!inQ.empty()){
            current_time++;
            cout<<current_time<<' ';
        }
        if(!Q.isEmpty()){
            process P = Q.extractMin();
            P.setStartTime(current_time);
            current_time = current_time + P.getBurstTime();
            P.setFinishTime(current_time);
            WaitingTime.push_back(P.Waiting_Time());
            TurnAroundTime.push_back(P.TurnAround_Time());
            cout<<'P'<<P.getPid()<<' '<<current_time<<' ';
        }
    }
    while(inQ.empty()&&!Q.isEmpty()){
        process P = Q.extractMin();
        P.setStartTime(current_time);
        current_time = current_time + P.getBurstTime();
        P.setFinishTime(current_time);
        WaitingTime.push_back(P.Waiting_Time());
        TurnAroundTime.push_back(P.TurnAround_Time());
        cout<<'P'<<P.getPid()<<' '<<current_time<<' ';
    }
    cout<<endl;
    int TotalWaitingTime=0;
    int TotalTurnAroundTime=0;
    for(int W : WaitingTime)
        TotalWaitingTime += W;
    for(int T : TurnAroundTime)
        TotalTurnAroundTime += T;
//    cout<<"Total Waiting Time: "<<TotalWaitingTime<<endl;
//    cout<<"Total Turn Around Time: "<<TotalTurnAroundTime<<endl;
    int AverageTotalWaitingTime = TotalWaitingTime/WaitingTime.size();
    int AverageTotalTurnAroundTime = TotalTurnAroundTime/TurnAroundTime.size();
    cout<<"Average Total Waiting Time: "<<AverageTotalWaitingTime<<endl;
    cout<<"Average Total Turn Around Time: "<<AverageTotalTurnAroundTime<<endl;


}

#endif // NON-PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
