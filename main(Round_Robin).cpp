//
// Created by MAGDY on 4/18/2024.
//
#include <iostream>
#include <vector>
#include"PROCESS.h"

using namespace std;
int main(){

    vector<process>processes;
    // Initialize an empty vector of processes
    process p1={1,0,5};
    process p2={2,1,3};
    process p3={3,3,6};
    process p4={4,5,1};
    process p5={5,6,4};
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
