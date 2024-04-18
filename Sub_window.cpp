#include "sub_window.h"
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_sub_window.h"
#include <windows.h>

#include <QElapsedTimer>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>

extern int ch;
extern int num;
extern process p[10], p1[10], temp;
extern queue<int> q1;
int time_slice;
int condition = 0;
//const int Dpi=100;
//int Slider_Value;
sub_window::sub_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sub_window)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    //scene->setSceneRect(0,0,200,100);
    QStringList header;
    header << "ID"
           << "Arrival Time"
           << "Burst Time"
           << "Priority"
           << "Color";
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
    ui->lineEdit_timeslice->setPlaceholderText("Input time slice...");

}

void sub_window::shortest_job_sort(int n)
{
    int i, j;
    for (i = 2; i <= n; i++) {
        for (j = 1; j <= i; j++) {
            if (p[j].at > p[i].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            } else if (p[j].at == p[i].at) {
                if (p[j].bt > p[i].bt) {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void sub_window::displayturnwait(int n)
{
    int i;
    int j;
    for (i = 1; i <= num; i++) {
        p[i].tat = p[i].ft - p1[i].at;
        p[i].wt = p[i].tat - p1[i].bt;
        p[0].tat = p[0].tat + p[i].tat;
        p[0].wt = p[0].wt + p[i].wt;
    }

    p[0].tat = p[0].tat / n;
    p[0].wt = p[0].wt / n;

    QStringList header;
    header << "ID"
           << "Finish Time"
           << "Turnaround Time"
           << "Waiting Time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(4);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet(
        "QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet(
        "QHeaderView::section{background:green;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2, 150);

    for (i = 0; i <= ui->tableWidget_Result->rowCount(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        QString temp_string = QString::number(p[i + 1].id);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i, 0, item);
    }

    for (i = 0; i <= ui->tableWidget_Result->rowCount(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        QString temp_string = QString::number(p[i + 1].ft);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i, 1, item);
    }

    for (i = 0; i <= ui->tableWidget_Result->rowCount(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        QString temp_string = QString::number(p[i + 1].tat);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i, 2, item);
    }

    for (i = 0; i <= ui->tableWidget_Result->rowCount(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem();
        QString temp_string = QString::number(p[i + 1].wt);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i, 3, item);
    }
}

sub_window::~sub_window()
{
    delete ui;
}

void sub_window::on_pushButton_clicked()
{
    int temp_data[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    QString tableData[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            tableData[i][j] = ui->tableWidget->item(i, j)->text();
        }
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount() - 1; j++) {
            temp_data[i][j] = tableData[i][j].toInt();
        }
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        p[i + 1].id = temp_data[i][0];
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        p[i + 1].at = temp_data[i][1];
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        p[i + 1].bt = temp_data[i][2];
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        p[i + 1].pr = temp_data[i][3];
    }

    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        p[i + 1].color = tableData[i][4];
    }

    QString text_tempa = ui->lineEdit_timeslice->text();
    time_slice = text_tempa.toInt();

    if (time_slice == 0) {
        QMessageBox::warning(this, "Warning", "Please Input The Time Slice!!!");
    } else {
        condition += 1;
    }


}

void sub_window::on_pushButton_2_clicked()
{
    if (ui->radioButton_Sub_FCFS->isChecked()) {
        ch = 1;
        condition += 1;
    } else if (ui->radioButton_Sub_NSJF->isChecked()) {
        ch = 2;
        condition += 1;
    } else if (ui->radioButton_Sub_PSJF->isChecked()) {
        ch = 3;
        condition += 1;
    } else if (ui->radioButton_Sub_RR->isChecked()) {
        ch = 4;
        condition += 1;
    } else if (ui->radioButton_Sub_PR->isChecked()) {
        ch = 5;
        condition += 1;
    } else {
        QMessageBox::warning(this, "Warning", "Please select an algorithm!");
    }

    // Check if the condition is greater than or equal to 2
    if (condition >= 2) {
        // Algorithms usage begins here
        // Check if ch == 1 (assuming it's the first scheduling algorithm)
        if (ch == 1) {
            int i;

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {
                p1[i] = p[i];
            }

            // Calculate start and finish times for each process
            p[1].st = p[1].at;
            for (i = 2; i <= num; i++) {
                p[i].st = p[i - 1].st + p[i - 1].bt;
            }

            p[1].ft = p[1].bt;
            for (i = 2; i <= num; i++) {
                p[i].ft = p[i - 1].ft + p[i].bt;
            }

            // Display the Gantt chart
            QBrush color_brush(QColor(p[1].color));
            QPen blackpen(Qt::black);
            blackpen.setWidth(1);
            QElapsedTimer t;
            t.start();
            rectangle = scene->addRect(-200,
                                       0,
                                       Rectangle_Width * p[1].bt,
                                       Rectangle_Height,
                                       blackpen,
                                       color_brush);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem("0");
            txtitem->setPos(QPointF(-200, 100));
            scene->addItem(txtitem);

            // Wait for visualization
            while (t.elapsed() < 2500) {
                QCoreApplication::processEvents();
            }

            // Draw rectangles for each process and display its finish time
            for (i = 2; i <= num; i++) {
                QBrush color_brush(QColor(p[i].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle = scene->addRect(-200 + Rectangle_Width * p[i - 1].ft,
                                           0,
                                           Rectangle_Width * p[i].bt,
                                           Rectangle_Height,
                                           blackpen,
                                           color_brush);
                QString temp_str = QString::number(p[i - 1].ft);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200 + Rectangle_Width * p[i - 1].ft, 100));
                scene->addItem(txtitem);

                // Wait for visualization
                QElapsedTimer t;
                t.start();
                while (t.elapsed() < 2500) {
                    QCoreApplication::processEvents();
                }
            }

            // Display the finish time of the last process
            QString temp_str = QString::number(p[num].ft);
            QGraphicsTextItem *txtitema = new QGraphicsTextItem(temp_str);
            txtitema->setPos(QPointF(-200 + Rectangle_Width * p[num].ft, 100));
            scene->addItem(txtitema);

            // Reset condition
            condition = 0;

            // Display turnaround and waiting times
            displayturnwait(num);

            // Show information message box indicating completion
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }



        // Check if ch == 2 (assuming it's the second scheduling algorithm)
        if (ch == 2) {
            // Initialize variables
            int i, limit, nextval, m, min, pre_min;

            // Set initial turnaround and waiting times
            p[0].wt = p[0].tat = 0;

            // Calculate the time limit for scheduling
            limit = p[1].at;
            for (i = 1; i <= num; i++) {
                limit += p[i].bt;
            }

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {
                p1[i] = p[i];
            }

            // Initialize nextval with arrival time of first process
            nextval = p[1].at;
            m = 1;
            pre_min = 1;

            // Wait for visualization
            QElapsedTimer t;
            t.start();
            while (t.elapsed() < 2500) {
                QCoreApplication::processEvents();
            }

            // Execute Shortest Job First (SJF) scheduling algorithm
            do {
                min = 9999;
                for (i = 1; p[i].at <= nextval && i <= num; i++) {
                    // Find the process with the shortest burst time that has arrived
                    if (p[i].bt < min && p[i].bt > 0) {
                        m = i;
                        min = p[i].bt;
                    }
                }
                // Update nextval with the completion time of the selected process
                nextval += p[m].bt;

                // Draw rectangle representing execution of the selected process
                QBrush color_brush(QColor(p[m].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle = scene->addRect(-200 + Rectangle_Width * p[pre_min].ft,
                                           0,
                                           Rectangle_Width * p[m].bt,
                                           Rectangle_Height,
                                           blackpen,
                                           color_brush);
                QString temp_str = QString::number(p[pre_min].ft);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200 + Rectangle_Width * p[pre_min].ft, 100));
                scene->addItem(txtitem);

                // Update remaining burst time of the selected process
                p[m].bt = 0;

                // Update finish time, turnaround time, and waiting time of the selected process
                if (p[m].bt == 0) {
                    p[m].ft = nextval;
                    p[m].tat = p[m].ft - p[m].at;
                    p[m].wt = p[m].tat - p1[m].bt;
                    p[0].tat += p[m].tat;
                    p[0].wt += p[m].wt;
                }

                // Update pre_min for next iteration
                pre_min = m;

                // Wait for visualization
                QElapsedTimer t;
                t.start();
                while (t.elapsed() < 2500) {
                    QCoreApplication::processEvents();
                }
            } while (nextval < limit);

            // Display the finish time of the last executed process
            QString temp_str = QString::number(p[m].ft);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * p[m].ft, 100));
            scene->addItem(txtitem);

            // Reset condition
            condition = 0;

            // Display turnaround and waiting times
            displayturnwait(num);

            // Show information message box indicating completion
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }


        if (ch == 3) {
            // Sort processes based on their burst times in ascending order (Shortest Job First)
            shortest_job_sort(num);

            // Initialize variables
            int i, limit, nextval, m, min;
            p[0].wt = p[0].tat = 0;

            // Calculate the total time required to execute all processes
            limit = p[1].at;
            for (i = 1; i <= num; i++) {
                limit += p[i].bt;
            }

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {
                p1[i] = p[i];
            }

            // Set the initial time value and display it on the scene
            nextval = p[1].at;
            m = 1;
            QString temp_str = QString::number(p[1].at);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200, 100));
            scene->addItem(txtitem);

            // Execute SJF scheduling algorithm
            do {
                min = 9999;
                // Find the process with the shortest remaining burst time
                for (i = 1; p[i].at <= nextval && i <= num; i++) {
                    if (p[i].bt < min && p[i].bt > 0) {
                        m = i;
                        min = p[i].bt;
                    }
                }
                // Execute the selected process for one time unit
                nextval += 1;
                p[m].bt = p[m].bt - 1;

                // Draw a rectangle representing the current time unit
                QBrush color_brush(QColor(p[m].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle = scene->addRect(-200 + Rectangle_Width * nextval,
                                           0,
                                           Rectangle_Width,
                                           Rectangle_Height,
                                           blackpen,
                                           color_brush);
                // Display the current time unit on top of the rectangle
                QString temp_str = QString::number(nextval);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval + 1, 100));
                scene->addItem(txtitem);

                // Wait for approximately 2.5 seconds for visualization
                QElapsedTimer t;
                t.start();
                while (t.elapsed() < 2500) {
                    QCoreApplication::processEvents();
                }

                // Update process data if the current process is completed
                if (p[m].bt == 0) {
                    p[m].ft = nextval;
                    p[m].tat = p[m].ft - p[m].at;
                    p[m].wt = p[m].tat - p1[m].bt;
                    p[0].tat += p[m].tat;
                    p[0].wt += p[m].wt;
                }
            } while (nextval < limit);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(num);
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        // Check if ch == 4
        if (ch == 4) {
            // Initialize variables
            int i, m, nextval, nextarr;

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {
                p1[i] = p[i];
            }

            // Set initial values for nextval and nextarr
            nextval = p[1].at;

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

        // Check if ch == 5
        if (ch == 5) {
            // Initialize variables
            int i, j, nextval;

            // Sort processes based on priority and arrival time
            for (i = 1; i <= num; i++) {
                for (j = i; j <= num; j++) {
                    // Sort by priority
                    if (p[i].pr > p[j].pr) {
                        // Swap processes if priority is higher for process j
                        temp = p[j];
                        p[j] = p[i];
                        p[i] = temp;
                    }
                    // If priorities are equal, sort by arrival time
                    if ((p[i].pr == p[j].pr)) {
                        if (p[i].at > p[j].at) {
                            // Swap processes if arrival time is higher for process j
                            temp = p[j];
                            p[j] = p[i];
                            p[i] = temp;
                        }
                    }
                }
            }

            // Create a copy of the original process data
            for (i = 1; i <= num; i++) {
                p1[i] = p[i];
            }

            // Initialize nextval with arrival time of first process
            nextval = p[1].at;
            p[1].ft = p[1].bt;

            // Execute processes in sorted order
            for (i = 1; i <= num; i++) {
                // Draw a rectangle representing execution of the process
                QBrush color_brush(QColor(p[i].color));
                QPen blackpen(Qt::black);
                blackpen.setWidth(1);
                rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                           0,
                                           Rectangle_Width * p[i].bt,
                                           Rectangle_Height,
                                           blackpen,
                                           color_brush);
                // Display the current time value on top of the rectangle
                QString temp_str = QString::number(nextval);
                QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                scene->addItem(txtitem);

                // Update nextval with the completion time of the current process
                nextval += p[i].bt;
                p[i].ft = nextval;

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
        } else {
            // Display a warning message if ch is not equal to 5
            QMessageBox::warning(this, "Warning", "Check your data!");
        }

    }
}
void sub_window::on_pushButton_4_clicked()
{
    scene->clear();
    for (int i = 0; i < num; i++) {
        p[i].at = 0;
        p[i].bt = 0;
        p[i].color = "";
        p[i].ft = 0;
        p[i].id = 0;
        p[i].pr = 0;
        p[i].st = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }

    QStringList header;
    header << "ID"
           << "Finish Time"
           << "Turnaround Time"
           << "Waiting Time";
    ui->tableWidget_Result->setRowCount(num);
    ui->tableWidget_Result->setColumnCount(4);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet(
        "QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet(
        "QHeaderView::section{background:green;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2, 150);
}
