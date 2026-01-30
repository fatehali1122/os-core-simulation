#include <stdio.h>
#include "process.h"
#include "process_scheduler.h"    //Linkage
#include "file_system.h"       


void showMenu(void)
{
    printf("\n===== OS PROCESS SIMULATOR =====\n");
    printf("1. Create Process\n");
    printf("2. Change Process State\n");
    printf("3. Schedule Next Process (FCFS)\n");
    printf("4. Schedule Next Process (Round Robin)\n");
    printf("5. Schedule Next Process (Priority Scheduling)\n");
    printf("6. Terminate Process\n");
    printf("7. Show Process List\n");
    printf("8. Create File\n");
    printf("9. Write File\n");
    printf("10. Read File\n");
    printf("11. Delete File\n");
    printf("12. Show File List\n");
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
int main() 
{
    int choice;
    while (1) {

        showMenu();
        scanf("%d", &choice);
        if (choice == 0)
            break;

        if (choice == 1) 
        {
            int p, b, m;
            printf("Priority BurstTime MemoryUsage: ");
            scanf("%d %d %d", &p, &b, &m);
            int pid = processCreation(p, b, m);
            printf("Process created with PID %d\n", pid);
        }

        else if (choice == 2) 
        {
            int pid;
            printf("Enter PID: ");
            scanf("%d", &pid);
            changeProcessState(pid);
        }

        else if (choice == 3) 
        {
            dispatchFCFS();
        }

        else if (choice == 4) 
        {
            
            dispatchRR(2); // Quantum of 2
        }

        else if (choice == 5) 
        {
            dispatchPriority();
        }
        else if (choice == 6) 
        {
            int pid;
            printf("Enter PID: ");
            scanf("%d", &pid);
            terminateProcess(pid);
        }

        else if (choice == 7)
        {
            printProcessList();
        }
        else if (choice == 8) 
        {
            char name[32];
            int perm;
            printf("File name: ");
        scanf("%s", name);
        printf("Permissions (1=R, 2=W, 3=RW): ");
        scanf("%d", &perm);
        fs_createFile(name, perm);
        }
        else if (choice == 9) 
        {
            char name[32];
            char data[128];
            printf("File name: ");
            scanf("%s", name);
            printf("Data: ");
            scanf(" %[^\n]", data);
            fs_writeFile(name, data);
        }
        else if (choice == 10) 
        {
            char name[32];
            printf("File name: ");
            scanf("%s", name);
            fs_readFile(name);
        }
        else if (choice == 11) 
        {
            char name[32];
            printf("File name: ");
            scanf("%s", name);
            fs_deleteFile(name);
        }
        else if (choice == 12) 
        {
            fs_listFiles();
        }
    }
    
    fs_cleanup(); 
    return 0;
}