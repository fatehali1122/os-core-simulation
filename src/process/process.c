#include <stdio.h>
#include "memory_manager.h"           //Linkage

static int count = 0;          //global variable for assigning unique PID
struct PCB processTable[100];
static int processTableCount = 0;

int processCreation(int priority,int burstTime,int memoryUsage)
{
    if(processTableCount > 100)
    {
        printf("Array is full \n");
        return -1;
    }
    struct PCB p1;

    p1.pid = ++count;
    p1.status = NEW;
    p1.priority = priority;
    p1.burstTime = burstTime;
    p1.memoryUsage = memoryUsage;

    //Now storing this PCB in processTable Array
    processTable[processTableCount] = p1;
    processTableCount++;

    return p1.pid;   
}

void changeProcessState(int pid)
{
    int found = 0;
    for(int i = 0;i < processTableCount;i++)
    {
        if(processTable[i].pid == pid)
        {
            found = 1;
            switch(processTable[i].status)
            {
                case NEW:
                processTable[i].status = READY;
                printf("Status: NEW --> READY\n");
                break;

                case READY:
                processTable[i].status = RUNNING;
                printf("Status: READY --> RUNNING\n");

                break;
                
                case RUNNING:
                processTable[i].status = WAITING;
                printf("Status: RUNNING --> WAITING\n");
                break;

                case WAITING:
                processTable[i].status = READY;
                printf("Status: WAITING --> READY\n");
                break;
                
                default:
                printf("INVALID STATE\n");
                break;
            }

        }        
    }
    if(found == 0)
    {
        printf("Process with this pid not found\n");
    }
}
/*void terminateProcess(int pid) {
	
	int found = 0;
	
	for(int i = 0; i < 100; i++) {
		
		if(processTable[i].pid == pid && processTable[i].used == 1) {
		
			processTable[i].status = TERMINATED;
			processTable[i].used = 0; //Free slot
			printf("Process %d Terminated.\n", pid);
			found = 1;	
			break;
			
			
		}

	}
	if(found == 0) {
			
			printf("Process %d not found or does not exist", pid);
						
		}
	
	
}*/
void terminateProcess(int pid) {
	
    int found = 0;

    for(int i = 0; i < processTableCount; i++) {
        if(processTable[i].pid == pid) {
            
            for(int j = i; j < processTableCount - 1; j++) {
                processTable[j] = processTable[j+1];
            }
            
            processTableCount--;
            printf("Process %d Terminated.\n", pid);
            found = 1;
            break;
        }
    }
    
    if(found == 0) {
        printf("Process %d not found or does not exist\n", pid);
    }
}

int getprocessTableCount()
{
    return processTableCount;
}
