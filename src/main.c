
#include <stdio.h>
#include <string.h>
#include "../include/syscall.h"

#define MAX_NAME 32
#define MAX_DATA 256

void show_menu(void)
{
    printf("\n====== OS SIMULATION MENU ======\n");
    printf("1. Create Process\n");
    printf("2. Terminate Process\n");
    printf("3. Allocate Memory\n");
    printf("4. Deallocate Memory\n");
    printf("5. Create File\n");
    printf("6. Write File\n");
    printf("7. Read File\n");
    printf("8. Show Process List\n");
    printf("9. Show Memory Map\n");
    printf("10. List Files\n");
    printf("11.Change Process State\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

int main(void)
{
    int choice;
    sys_init();

    while (1)
    {
        show_menu();

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
        {
            int priority, burst, mem;
            printf("Priority BurstTime MemoryUsage: ");
            scanf("%d %d %d", &priority, &burst, &mem);
            int pid = sys_create_process(priority, burst, mem);
            if (pid != -1)
                printf("Process created with PID %d\n", pid);
            break;
        }

        case 2:
        {
            int pid;
            printf("PID to terminate: ");
            scanf("%d", &pid);
            sys_terminate_process(pid);
            break;
        }

        case 3:
        {
            int pid, size, strategy;
            printf("PID Size Strategy(1=FF,2=BF,3=WF)\n");
            printf("PID Size Strategy: ");
            scanf("%d %d %d", &pid, &size, &strategy);
            sys_allocate_memory(pid, size, strategy);
            break;
        }

        case 4:
        {
            int pid;
            printf("PID to deallocate memory: ");
            scanf("%d", &pid);
            sys_deallocate_memory(pid);
            break;
        }

        case 5:
        {
            char name[MAX_NAME];
            int perm;
            printf("File name & permissions: ");
            scanf("%s %d", name, &perm);
            sys_create_file(name, perm);
            break;
        }

        case 6:
        {
            char name[MAX_NAME];
            char data[MAX_DATA];
            printf("File name: ");
            scanf("%s", name);
            getchar();
            printf("Data: ");
            fgets(data, MAX_DATA, stdin);
            data[strcspn(data, "\n")] = 0;
            sys_write_file(name, data);
            break;
        }

        case 7:
        {
            char name[MAX_NAME];
            printf("File name: ");
            scanf("%s", name);
            sys_read_file(name);
            break;
        }

        case 8:
            sys_get_process_list();
            break;

        case 9:
            sys_get_memory_map();
            break;

        case 10:
            sys_list_files();
            break;

        case 11:
            int pid;
            printf("PID to change state: ");
            scanf("%d", &pid);
            sys_change_process_state(pid);
            break;

        default:
            printf("Invalid option\n");
        }
    }

    printf("Exiting OS Simulation...\n");
    return 0;
}

