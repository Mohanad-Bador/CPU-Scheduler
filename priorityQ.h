#ifndef PRIORITYQ_H_INCLUDED
#define PRIORITYQ_H_INCLUDED

#include <iostream>
#include <vector>
#include "process.h"

using namespace std;

bool comparePriority(const process &p1, const process &p2);

class PriorityQueue
{
private:
    vector<process> processes;

public:
    void insert(const process &p);
    process extractMin();
    bool isEmpty();
};

#endif // PRIORITYQ_H_INCLUDED
