#ifndef PROCESS_CPP_INCLUDED
#define PROCESS_CPP_INCLUDED

#include "process.h"


// Default constructor
process::process() {
    pid = 0;
    arrival_time = -1;
    burst_time = -1;
    priority = 0;
}

// Parameterized constructor
process::process(int pid, int arrival_time, int burst_time) {
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->burst_time = burst_time;
}


// Parameterized constructor with Priority
process::process(int pid, int arrival_time, int burst_time, int priority) {
    this->pid = pid;
    this->arrival_time = arrival_time;
    this->burst_time = burst_time;
    this->priority = priority;
    this->remaining_time = burst_time;
}

// Getter methods
int process::getPid() const {
    return pid;
}

int process::getArrivalTime() const {
    return arrival_time;
}

int process::getBurstTime() const {
    return burst_time;
}

int process::getRemainingTime() const {
    return remaining_time;
}

int process::getStartTime() const {
    return start_time;
}

int process::getFinishTime() const {
    return finish_time;
}

int process::getPriority() const {
    return priority;
}

void process::setBurstTime(int new_burst_time){
    this->burst_time = new_burst_time;
}

void process::setRemainingTime(int new_remaining_time){
    this->remaining_time = new_remaining_time;
}

void process::setStartTime(int new_start_time){
    this->start_time = new_start_time;
}

void process::setFinishTime(int new_finish_time){
    this->finish_time = new_finish_time;
}

void process::setPriority(int new_priority){
    this->priority = new_priority;
}


int process::Waiting_Time(){
    return (finish_time - arrival_time - burst_time);
}

int process::TurnAround_Time(){
    return (finish_time - arrival_time);
}

void process::printProcess(){
    cout << "Process ID: " << pid << ", Arrival Time: " << arrival_time << ", Burst Time: " << burst_time << ", Priority: " << priority << endl;
}

#endif // PROCESS_CPP_INCLUDED
