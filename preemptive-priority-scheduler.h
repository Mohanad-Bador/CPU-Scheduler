#ifndef PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
#define PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED

#include <algorithm>
#include "process.h"
#include "priorityQ.h"

void P_Priority(vector<process> &inQ , int &current_time){
    PriorityQueue Q;
    vector<int> WaitingTime;
    vector<int> TurnAroundTime;
    cout<<"Gantt Chart For P Priority Scheduler"<<endl;
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
            if(P.getRemainingTime()==P.getBurstTime()){
                P.setStartTime(current_time);
            }
            if(P.getRemainingTime()>0){
                P.setRemainingTime(P.getRemainingTime()-1);
                Q.insert(P);
                current_time++;
                cout<<'P'<<P.getPid()<<' '<<current_time<<' ';
            }
            else{
                P.setFinishTime(current_time);
                WaitingTime.push_back(P.Waiting_Time());
                TurnAroundTime.push_back(P.TurnAround_Time());
            }
        }
    }
    while(inQ.empty()&&!Q.isEmpty()){
        process P = Q.extractMin();
        if(P.getRemainingTime()==P.getBurstTime()){
            P.setStartTime(current_time);
        }
        if(P.getRemainingTime()>0){
            P.setRemainingTime(P.getRemainingTime()-1);
            Q.insert(P);
            current_time++;
            cout<<'P'<<P.getPid()<<' '<<current_time<<' ';
        }
        else{
            P.setFinishTime(current_time);
            WaitingTime.push_back(P.Waiting_Time());
            TurnAroundTime.push_back(P.TurnAround_Time());
        }
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

#endif // PREEMPTIVE-PRIORITY-SCHEDULER_H_INCLUDED
