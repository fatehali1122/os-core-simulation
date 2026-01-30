/* =============================================================
 * MAIN SIMULATION CONTROLLER
 * Acts as the "Motherboard" connecting User, CPU, and Kernel.
 * ============================================================= */

#include <stdio.h>
#include <stdlib.h>

// Include the Public APIs
#include "syscall.h"
#include "process_scheduler.h"
#include "file_system.h" // For permissions flags

void printHeader(const char* title) {
    printf("\n=========================================\n");
    printf("  %s\n", title);
    printf("=========================================\n");
}

void waitForEnter() {
    printf("\n[Press Enter to Continue]");
    while(getchar() != '\n');
    getchar(); // Catch the newline
}

// --- SUB-MENUS ---

void menu_filesystem() {
    int choice;
    char name[32];
    char content[100];

    do {
        printHeader("FILE SYSTEM MENU");
        sys_list_files(); 
        printf("\n1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("0. Back\n");
        printf("Select: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Filename: "); scanf("%s", name);
                // Create with Read(1) + Write(2) = 3 permissions
                if(sys_create_file(name, 3) == 0) printf("Success.\n");
                break;
            case 2:
                printf("Filename: "); scanf("%s", name);
                printf("Content: "); scanf(" %[^\n]", content); // Read line
                sys_write_file(name, content);
                break;
            case 3:
                printf("Filename: "); scanf("%s", name);
                sys_read_file(name);
                break;
            case 4:
                printf("Filename: "); scanf("%s", name);
                sys_delete_file(name);
                break;
            case 0: break;
        }
        if(choice != 0) waitForEnter();
    } while(choice != 0);
}

void menu_processes() {
    int choice, pid, prio, burst, mem;
    
    do {
        printHeader("PROCESS MANAGEMENT");
        sys_get_process_list();
        printf("\n1. Create New Process\n");
        printf("2. Terminate Process\n");
        printf("0. Back\n");
        printf("Select: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Priority (0-Highest): "); scanf("%d", &prio);
                printf("Burst Time: "); scanf("%d", &burst);
                printf("Memory (MB): "); scanf("%d", &mem);
                
                pid = sys_create_process(prio, burst, mem);
                if (pid != -1) 
                    printf("Process Created Successfully. PID: %d\n", pid);
                else 
                    printf("Failed to create process (Memory Full?).\n");
                break;
            case 2:
                printf("Enter PID to Kill: "); scanf("%d", &pid);
                if(sys_terminate_process(pid) == 0)
                    printf("Process %d Terminated.\n", pid);
                else
                    printf("Failed to terminate process.\n");
                break;
            case 0: break;
        }
        if(choice != 0) waitForEnter();
    } while (choice != 0);
}

// --- MAIN LOOP ---

int main() {
    int choice;
    
    // 1. BOOT THE SYSTEM
    printHeader("BOOTING OS SIMULATION...");
    sys_init(); 
    
    // Create some default processes for testing
    printf("\n[BOOT] Loading background services...\n");
    sys_create_process(1, 50, 100); // PID 1
    sys_create_file("boot.log", 3);
    sys_write_file("boot.log", "System Booted Successfully.");

    // 2. MAIN KERNEL LOOP
    while(1) {
        // A. EXECUTE PENDING INTERRUPTS (The Hardware Phase)
        // This checks if any timers or I/O events occurred
        sys_execute_interrupts();

        // B. USER INTERFACE
        printHeader("KERNEL DASHBOARD");
        printf("1. Process Manager (Create/Kill)\n");
        printf("2. File System\n");
        printf("3. Memory Map\n");
        printf("-----------------------------\n");
        printf("4. [CPU] Run Scheduler (Round Robin)\n");
        printf("5. [CPU] Run Scheduler (Priority)\n");
        printf("6. [CPU] Run Scheduler (FCFS)\n");
        printf("-----------------------------\n");
        printf("7. [HW] Trigger I/O Interrupt (Simulate Disk)\n");
        printf("8. [HW] Trigger Timer Interrupt (Simulate Clock)\n");
        printf("0. Shutdown\n");
        printf("Select: ");
        
        scanf("%d", &choice);

        int pid;
        switch(choice) {
            case 1: 
                menu_processes(); 
                break;
                
            case 2: 
                menu_filesystem(); 
                break;
                
            case 3: 
                sys_get_memory_map(); 
                waitForEnter(); 
                break;

            case 4: // ROUND ROBIN
                printf("\n--- CPU RUNNING (Round Robin Q=20) ---\n");
                dispatchRR(20); 
                waitForEnter();
                break;

            case 5: // PRIORITY
                printf("\n--- CPU RUNNING (Priority) ---\n");
                dispatchPriority();
                waitForEnter();
                break;
                
            case 6: // FCFS
                printf("\n--- CPU RUNNING (FCFS) ---\n");
                dispatchFCFS();
                waitForEnter();
                break;

            case 7: // INTERRUPT: I/O
                printf("Enter PID requesting I/O: "); scanf("%d", &pid);
                // This raises the interrupt -> Queued -> Handle -> Process Blocked
                if(sys_io_request(pid) == 0)
                    printf("I/O Interrupt Raised for PID %d (Will process on next cycle)\n", pid);
                else
                    printf("Invalid PID.\n");
                waitForEnter();
                break;

            case 8: // INTERRUPT: TIMER
                printf("Enter PID to Preempt: "); scanf("%d", &pid);
                // This raises the interrupt -> Queued -> Handle -> Process Ready
                if(sys_scheduler_timer(pid) == 0)
                    printf("Timer Interrupt Raised for PID %d\n", pid);
                else
                    printf("Invalid PID.\n");
                waitForEnter();
                break;

            case 0:
                printf("Shutting down...\n");
                exit(0);

            default:
                printf("Invalid selection.\n");
        }
    }

    return 0;
}