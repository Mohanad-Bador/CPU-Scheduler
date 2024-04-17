#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED
using namespace std;

struct process
{
    int id;
    int at; // Arrival time
    int bt; // Burst time
    int pr; // Priority
    int st; // Start time
    int ft; // Finish time
    int rt; // Remaining time

    float wt;  // Waiting time
    float tat; // Turnaround time

    // QString color;
};

#endif // PROCESS_H_INCLUDED

// class process{
// private:
//     int pid;
//     int arrival_time;
//     int burst_time;
//     int remaining_time;
//     int start_time;
//     int finish_time;
//     int priority;
//
//
// public:
//     process();
//     process(int pid, int arr_time, int burst_time);
//     process(int pid, int arr_time, int burst_time, int priority);
//
//     int getPid() const;
//     int getArrivalTime() const;
//     int getBurstTime() const;
//     int getRemainingTime() const;
//     int getStartTime() const;
//     int getFinishTime() const;
//     int getPriority() const;
//
//     void setBurstTime(int new_burst_time);
//     void setRemainingTime(int new_remaining_time);
//     void setStartTime(int new_start_time);
//     void setFinishTime(int new_finish_time);
//     void setPriority(int new_priority);
//
//     int Waiting_Time();
//     int TurnAround_Time();
//
//     void printProcess ();
//
// };
