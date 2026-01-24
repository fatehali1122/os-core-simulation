//Compile Command: make
//Run Command: ./os_simulation

#include <stdio.h>
#include "process.h"
#include "process_scheduler.h"

// Helper to visualize the whole chain
void printListSnapshot() {
    struct Node* temp = getProcessHead();
    
    printf("\n[SNAPSHOT] Current Process List:\n");
    if (temp == NULL) {
        printf("   (List is Empty)\n");
        return;
    }

    printf("   HEAD -> ");
    while(temp != NULL) {
        printf("[PID: %d | %s] -> ", temp->pcb.pid, getStateString(temp->pcb.status));
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {

    printf("\n========================================\n");
    printf("  TESTING: FCFS SCHEDULING (NEXT PROCESS)\n");
    printf("========================================\n");

    /* Create fresh processes for FCFS test */
    processCreation(1, 5, 100);  // PID 4
    processCreation(1, 5, 100);  // PID 5
    processCreation(1, 5, 100);  // PID 6

    printListSnapshot();

    /* Move all to READY */
    changeProcessState(1); // NEW -> READY
    changeProcessState(2); // NEW -> READY
    changeProcessState(3); // NEW -> READY

    printf("\n--- FCFS Step 1: Schedule Next Process ---\n");
    int nextPid = scheduleNextProcessFCFS();
    printf("Next Scheduled PID (Expected: 1): %d\n", nextPid);

    dispatchFCFS();
    printListSnapshot();

    printf("\n--- FCFS Step 2: Terminate Running Process ---\n");
    terminateProcess(1);
    printListSnapshot();

    printf("\n--- FCFS Step 3: Schedule Next Process ---\n");
    nextPid = scheduleNextProcessFCFS();
    printf("Next Scheduled PID (Expected: 2): %d\n", nextPid);

    dispatchFCFS();
    printListSnapshot();

    printf("\n--- FCFS Step 4: Terminate Running Process ---\n");
    terminateProcess(2);
    printListSnapshot();

    printf("\n--- FCFS Step 5: Schedule Last Process ---\n");
    nextPid = scheduleNextProcessFCFS();
    printf("Next Scheduled PID (Expected: 3): %d\n", nextPid);

    dispatchFCFS();
    printListSnapshot();

    printf("\n--- FCFS Step 6: Cleanup ---\n");
    terminateProcess(3);
    printListSnapshot();

    return 0;
}

