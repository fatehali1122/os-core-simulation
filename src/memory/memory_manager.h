#ifndef MEMORY_MANAGER_H   //This header file will be used multiple times,this we use this to define only once 
#define MEMORY_MANAGER_H

enum ProcessState
{
    NEW,READY,RUNNING,WAITING,TERMINATED
};

struct PCB
{
    int pid;
    int burstTime;
    int memoryUsage;
    enum ProcessState status;
    int priority;

};

//This funtions create a process
int processCreation(int priority,int burstTime,int memoryUsage);
//This funtion changes status of process
void changeProcessState(int pid);

#endif

