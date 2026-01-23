#include <stdio.h>
#include "process.h"

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


	printf("Size of PCB struct: %I64u\n", sizeof(struct PCB));
	printf("Size of Node struct: %I64u\n", sizeof(struct Node));

    printf("========================================\n");
    printf("  TESTING: STATE CHANGES & TERMINATION  \n");
    printf("========================================\n");

    // 1. SETUP: Create 3 Processes
    // List should be: 1 -> 2 -> 3
    processCreation(1, 10, 100); // PID 1
    processCreation(5, 20, 200); // PID 2
    processCreation(2, 15, 150); // PID 3
    printListSnapshot();

    // 2. TEST STATE CHANGES
    // We will move PID 2 (Middle process) to RUNNING
    printf("\n--- Test 1: Updating PID 2 States ---\n");
    
    changeProcessState(2); // NEW -> READY
    changeProcessState(2); // READY -> RUNNING
    
    // Verify that PID 1 is still NEW (Isolation check)
    printf("Checking PID 2 (Should be RUNNING)...\n");
    printListSnapshot();

    // 3. TEST WAITING LOOP
    // Move PID 2 to WAITING and back to READY
    printf("\n--- Test 2: The IO Wait Loop (PID 2) ---\n");
    changeProcessState(2); // RUNNING -> WAITING
    changeProcessState(2); // WAITING -> READY
    printListSnapshot();

    // 4. TEST TERMINATION (Middle Node)
    // Deleting PID 2. List should become: 1 -> 3
    printf("\n--- Test 3: Delete Middle Node (PID 2) ---\n");
    terminateProcess(2);
    printListSnapshot();

    // 5. TEST TERMINATION (Head Node)
    // Deleting PID 1. List should become: 3
    // This checks if your 'head = head->next' logic works.
    printf("\n--- Test 4: Delete Head Node (PID 1) ---\n");
    terminateProcess(1);
    printListSnapshot();

    // 6. TEST TERMINATION (Tail Node / Last one)
    // Deleting PID 3. List should become Empty.
    printf("\n--- Test 5: Delete Last Node (PID 3) ---\n");
    terminateProcess(3);
    printListSnapshot();

    // 7. TEST ERROR HANDLING
    printf("\n--- Test 6: Delete Non-Existent Process ---\n");
    terminateProcess(99); // Should print "not found"*/

    return 0;
}