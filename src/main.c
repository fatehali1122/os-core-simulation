
#include <stdio.h>
#include <stdlib.h>
#include "../include/process.h"             
#include "../include/process_scheduler.h"   
#include "../include/memory.h"

void showMenu(void)
{
    printf("\n===== OS PROCESS SIMULATOR =====\n");
    printf("1. Create Process\n");
    printf("2. Change Process State\n");
    printf("3. Schedule Next Process (FCFS)\n");
    printf("4. Schedule Next Process (Round Robin)\n");
    printf("5. Schedule Next Process (Priority)\n");
    printf("6. Terminate Process\n");
    printf("7. Show Process List\n");
    printf("8. Show Memory Map\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

void printProcessList(void)
{
    struct Node *temp = getProcessHead();
    printf("\nPID   PRIO  BURST  STATE\n");
    printf("----------------------------\n");

    while (temp != NULL) {
        printf("%-5d %-5d %-5d  %s\n",
               temp->pcb.pid,
               temp->pcb.priority,
               temp->pcb.burstTime,
               getStateString(temp->pcb.status));
        temp = temp->next;
    }
}

int main() {
  
    sched_init();       
    initializeMemory(); 

    printf("------ System Booting -----\n");
    
    int choice;

    while (1) {
        showMenu();
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue; 
        }

        if (choice == 0)
            break;

        if (choice == 1) {
            int p, b, m;
            printf("Priority BurstTime MemoryUsage: ");
            scanf("%d %d %d", &p, &b, &m);
            
            //  Try to allocate memory first
            // We use a temporary dummy PID (9999) to check if space exists.
            // Strategy 1 = First Fit
            int memAddr = allocateMemory(9999, m, 1); 
            
            if (memAddr == -1) {
                printf("Error: Process Creation Failed - Not enough memory!\n");
            } else {
                // Memory check passed. Free the dummy block.
                deallocateMemory(9999);
                
                //  Create the Process Struct
                int pid = processCreation(p, b, m);
                
                if (pid != -1) {
                    // Real Allocation with Real PID
                    allocateMemory(pid, m, 1);
                    printf("Process created with PID %d (Allocated at Addr: %d)\n", pid, memAddr);
                }
            }
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
            dispatchRR(2);
        }

        else if (choice == 5) {
            dispatchPriority();
        }

        
        else if (choice == 6) {
            int pid;
            printf("Enter PID: ");
            scanf("%d", &pid);
            
            //  Free the PCB
            terminateProcess(pid);
            
            //  Free the Memory
            deallocateMemory(pid);
        }

        else if (choice == 7) {
            printProcessList();
        }
        
        
        else if (choice == 8) {
            printMemoryMap();
            printFragmentationStats();
        }
    }
    
    return 0;
}

