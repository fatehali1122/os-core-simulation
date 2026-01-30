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

struct Node {
	
struct PCB pcb;
struct Node* next;
	
};

//This funtions create a process
int processCreation(int priority,int burstTime,int memoryUsage);
//terminates the process explicitly
void terminateProcess(int pid);
//getter for head node
struct Node* getProcessHead();
//getter for state of process
const char* getStateString(enum ProcessState s);
//To check if process exists or not (main purpose is to call it using helper funtion in syscall)
int processExists(int pid);

//state transitions made more robust
void processPreempt(int pid);	// Timer Interrupt [Running] -> [Ready]
void processBlock(int pid);		// I/O Request [Running] -> [Waiting]
void processWakeup(int pid);	// I/O complete [Waiting] -> [Ready]

#endif