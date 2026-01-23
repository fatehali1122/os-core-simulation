/*#include <stdio.h>
#include "process.h"     //Linkage


void showMenu(void)
{
    printf("\n===== OS PROCESS SIMULATOR =====\n");
    printf("1. Create Process\n");
    printf("2. Change Process State\n");
    printf("3. Schedule Next Process (FCFS)\n");
    printf("4. Terminate Process\n");
    printf("5. Show Process List\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void printProcessList(void)
{
    struct Node *temp = getProcessHead();
    printf("\nPID   STATE\n");
    printf("------------\n");

    while (temp != NULL) {
        printf("%-5d %s\n",
               temp->pcb.pid,
               getStateString(temp->pcb.status));
        temp = temp->next;
    }
}

// This is a temporary main function to test the build system
int main() {
    printf("------Before executing-----\n");
    int processId = processCreation(1,1,1);
	printf("Process ID: %d \n", processId);
	printf("Counter: %d\n\n",getprocessTableCount());

    printf("------After executing-----\n");
	terminateProcess(1);
    printf("Counter: %d\n\n",getprocessTableCount());

	printf("---Testing if process exists or not after execution---\n");
    changeProcessState(1); //changing non-existent process state
    terminateProcess(1);
     int choice;

    while (1) {
        showMenu();
        scanf("%d", &choice);

        if (choice == 0)
            break;

        if (choice == 1) {
            int p, b, m;
            printf("Priority BurstTime MemoryUsage: ");
            scanf("%d %d %d", &p, &b, &m);
            int pid = processCreation(p, b, m);
            printf("Process created with PID %d\n", pid);
        }

        else if (choice == 2) {
            int pid;
            printf("Enter PID: ");
            scanf("%d", &pid);
            changeProcessState(pid);
        }

        else if (choice == 3) {
            dispatchFCFS();
        }

        else if (choice == 4) {
            int pid;
            printf("Enter PID: ");
            scanf("%d", &pid);
            terminateProcess(pid);
        }

        else if (choice == 5) {
            printProcessList();
        }
    }
	
    return 0;
}*/
