#ifndef PROCESS_H   //This header file will be used multiple times,this we use this to define only once 
#define PROCESS_H

enum ProcessState
{
    NEW,READY,RUNNING,WAITING,TERMINATED
};

struct PCB
{
    int pid;
    int burstTime; //used flag (int used) deleted
    int memoryUsage;
    enum ProcessState status;
    int priority;

};

//This funtions create a process
int processCreation(int priority,int burstTime,int memoryUsage);
//This funtion changes status of process
void changeProcessState(int pid);
//terminates the process explicitly
void terminateProcess(int pid);
//This return array allocated size
int getprocessTableCount();



#endif

