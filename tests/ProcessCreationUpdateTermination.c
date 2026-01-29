/*#include <stdio.h>

#include "../include/process.h"
#include "../include/process_scheduler.h"

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
        printf("[PID: %d | Prio: %d | Burst: %d | %s] -> ", 
               temp->pcb.pid, 
               temp->pcb.priority, 
               temp->pcb.burstTime,
               getStateString(temp->pcb.status));
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    sched_init(); 

    // ==========================================
    // TEST 1: ROUND ROBIN
    // ==========================================
    printf("\n========================================\n");
    printf("  TEST 1: ROUND ROBIN (Quantum = 2)\n");
    printf("========================================\n");

    // Create 2 processes with long burst times
    int p1 = processCreation(1, 6, 100);  // PID 1, Burst 6
    int p2 = processCreation(1, 6, 100);  // PID 2, Burst 6

    changeProcessState(p1); // Ready
    changeProcessState(p2); // Ready

    printListSnapshot();

    printf("\n--- RR Step 1: Dispatch PID 1 (Quantum 2) ---\n");
    dispatchRR(2); // Should run PID 1 for 2 ticks. Remaining: 4. Re-queue.
    printListSnapshot();

    printf("\n--- RR Step 2: Dispatch PID 2 (Quantum 2) ---\n");
    
    dispatchRR(2); 
    printListSnapshot();

    // Clean up
    terminateProcess(p1);
    terminateProcess(p2);

    // ==========================================
    // TEST 2: PRIORITY SCHEDULING
    // ==========================================
    printf("\n========================================\n");
    printf("  TEST 2: PRIORITY SCHEDULING\n");
    printf("========================================\n");

    // Create processes with different priorities (Lower number = Higher Priority)
    int low_prio_pid = processCreation(10, 5, 100); // Priority 10 (Low)
    int high_prio_pid = processCreation(1, 5, 100); // Priority 1 (High)
    int mid_prio_pid = processCreation(5, 5, 100);  // Priority 5 (Mid)

    changeProcessState(low_prio_pid);
    changeProcessState(high_prio_pid);
    changeProcessState(mid_prio_pid);

    printListSnapshot();

    printf("\n--- Priority Step 1: Who runs first? (Expected: PID %d) ---\n", high_prio_pid);
    dispatchPriority(); // Should pick Priority 1
    printListSnapshot();

    printf("\n--- Priority Step 2: Who runs next? (Expected: PID %d) ---\n", mid_prio_pid);
    dispatchPriority(); // Should pick Priority 5
    printListSnapshot();

    printf("\n--- Priority Step 3: Cleanup ---\n");
    terminateProcess(low_prio_pid);
    printListSnapshot();

    return 0;
}*/