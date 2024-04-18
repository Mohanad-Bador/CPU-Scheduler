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

void Circular_Shift_Left(vector<process>&list);
vector<int> RR(int timequantum, vector<process> &Waiting_queue);

#endif // PROCESS_H_INCLUDED

