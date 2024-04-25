#include <iostream>
#include <vector>
#include "PROCESS.h" // Include the header file for the 'process' class

using namespace std;

vector<int> chart; // Gantt chart should be a vector of integers

/*
 * This function is used to shift processes so that the process which has burst time greater than the time quantum
 * gets shifted to the end of the ready queue.
 */
void Circular_Shift_Left(vector<process>& list) {
    process temp = list[0]; // Store the first process temporarily
    for (size_t i = 0; i < list.size() - 1; i++) {
        list[i] = list[i + 1]; // Shift each process one position to the left
    }
    list[list.size() - 1] = temp; // Place the temporarily stored process at the end
}

/*
 * This function implements the Round Robin scheduling algorithm.
 * Parameters:
 * - timequantum: Time quantum for Round Robin scheduling
 * - Waiting_queue: Vector containing processes in the waiting queue
 * Returns:
 * - Gantt chart showing the sequence of execution
 */
vector<int> RR(int timequantum, vector<process>& Waiting_queue) {
    bool flag = false; // Flag to indicate if circular shift is needed
    vector<process> Ready_queue; // Queue containing processes ready for execution
    int n = Waiting_queue.size(); // Total number of processes
    int time = 0; // Current time
    int arrived_processes = 0; // Number of processes that have arrived
    int finished_processes = 0; // Number of processes that have finished execution
    int ready_processes = 0; // Number of processes ready for execution
    int q = timequantum; // Time quantum for Round Robin

    // Loop until all processes finish execution
    while (finished_processes < n) {
       // int num_removed = 0; // Number of elements removed from Waiting_queue
       vector<int>num_removed={0};

        for (auto it = Waiting_queue.begin(); it != Waiting_queue.end(); /*No increment here*/) {
            if (time >= it->at) {
                Ready_queue.push_back(*it);
                arrived_processes++;
                ready_processes++;
                it = Waiting_queue.erase(it); // Erase and update iterator
            } else {
                ++it; // Move to the next element
            }
        }

        // If more than one process has arrived and circular shift has been performed, shift again
        if (arrived_processes > 1 && flag) {
            Circular_Shift_Left(Ready_queue);
        }



        // If no process is ready for execution, increment time and continue
        if (ready_processes == 0) {
            time++;
            continue;
        }

        // Execute processes in the ready queue using Round Robin scheduling
        if (Ready_queue[0].bt > 0) {
            flag = true; // Set flag to true indicating circular shift may be needed
            if (Ready_queue[0].bt > q) {
                chart.push_back(Ready_queue[0].id); // Add process ID to the Gantt chart
                Ready_queue[0].bt -= q; // Reduce remaining burst time by the time quantum
                time += q; // Increment time by the time quantum
            } else {
                chart.push_back(Ready_queue[0].id); // Add process ID to the Gantt chart
                time += Ready_queue[0].bt; // Increment time by the remaining burst time
                Ready_queue[0].bt = 0; // Set burst time of the process to 0 indicating completion
                Ready_queue[0].ft = time; // Set finish time of the process
                finished_processes++; // Increment the count of finished processes
                ready_processes--; // Decrement the count of processes ready for execution
            }
        }
    }

    return chart; // Return the Gantt chart
}

/*
 * // Check if ch == 4
        if (ch == 4) {
            // Initialize variables
            int i;
            int m, nextval, nextarr;

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {  //num ????
                p1[i] = p[i];
            }

            // Set initial values for nextval and nextarr  (Timer)
            nextval = p[1].at;   // error  p[first process]

            // Populate the queue with processes that have arrived before or at the current time
            for (i = 1; i <= num, p[i].at <= nextval; i++) {
                q1.push(p[i].id);
            }
            nextarr = p[1].at;

            // Execute Round Robin scheduling algorithm
            while (!q1.empty()) {
                // Get the next process from the queue
                m = q1.front();
                q1.pop();
//#######################################################################################################################
                // Check if remaining burst time is greater than or equal to time slice
                if (p[m].bt >= time_slice) {
                    // Draw a rectangle representing execution of the process for a time slice
                    QBrush color_brush(QColor(p[m].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + Rectangle_Width * nextval,
                                               0,
                                               Rectangle_Width * time_slice,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
                    scene->addItem(txtitem);

                    // Update nextval
                    nextval += time_slice;
                } else {
                    // Draw a rectangle representing execution of the remaining burst time of the process
                    QBrush color_brush(QColor(p[m].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + Rectangle_Width * nextval,
                                               0,
                                               Rectangle_Width * p[m].bt,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
                    scene->addItem(txtitem);

                    // Update nextval
                    nextval += p[m].bt;
                }

                // Update remaining burst time of the process
                p[m].bt -= time_slice;

                // Check if there are more processes to arrive before the next time slice
                if (nextval < nextarr) {
                    // Add the process back to the queue if it still has remaining burst time
                    if (p[m].bt > 0) {
                        q1.push(m);
                    }
                    // Update finish time of the process if it has completed execution
                    if (p1[m].bt <= 0) {
                        p[m].ft = nextval;
                    }
                } else {
                    // Add processes arriving before the next time slice to the queue
                    while (i <= num && p1[i].at <= nextval) {
                        q1.push(p[i].id);
                        i++;
                    }
                    // Update nextarr to the arrival time of the next process
                    if (i <= num) {
                        nextarr = p[i].at;
                    }
                    // Add the current process back to the queue if it still has remaining burst time
                    if (p[m].bt > 0) {
                        q1.push(m);
                    }
                    // Update finish time of the process if it has completed execution
                    if (p[m].bt <= 0) {
                        p[m].ft = nextval;
                    }
                }

                // Wait for approximately 2.5 seconds for visualization
                QElapsedTimer t;
                t.start();
                while (t.elapsed() < 2500) {
                    QCoreApplication::processEvents();
                }
            }

            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(num);
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
 */