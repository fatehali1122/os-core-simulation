#include <stdio.h>
#include "memory_manager.h"     //Linkage

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
	
    return 0;
}
/*#include <stdio.h>
#include "memory_manager.h"

void printHeader(char* title) {
    printf("\n------------------------------------------------\n");
    printf("   TESTING: %s\n", title);
    printf("------------------------------------------------\n");
}

int main() {
   
    printHeader("PCB CREATION & STORING");

    printf("[Action] Creating Process A (Priority 1)...\n");
    int pidA = processCreation(1, 10, 100);
    printf(" -> Result: Created PID %d\n", pidA);

    printf("[Action] Creating Process B (Priority 5)...\n");
    int pidB = processCreation(5, 20, 200);
    printf(" -> Result: Created PID %d\n", pidB);

    printf("[Action] Creating Process C (Priority 2)...\n");
    int pidC = processCreation(2, 15, 150);
    printf(" -> Result: Created PID %d\n", pidC);

    int count = getprocessTableCount();
    if(count == 3) {
        printf("\n[PASS] Storing PCBs: Count is 3 as expected.\n");
    } else {
        printf("\n[FAIL] Storing PCBs: Expected 3, but got %d.\n", count);
    }

    printHeader("UPDATING PCB STATES");
    
    printf("[Action] Moving Process %d (Start: NEW)\n", pidB);
    
    changeProcessState(pidB); // Should print NEW --> READY
    changeProcessState(pidB); // Should print READY --> RUNNING
    changeProcessState(pidB); // Should print RUNNING --> WAITING
    changeProcessState(pidB); // Should print WAITING --> READY (Loop back)

    // Verify independent state changes (Process A should still be NEW)
    printf("\n[Action] Moving Process %d (Should start at NEW)\n", pidA);
    changeProcessState(pidA); // Should print NEW --> READY

    printHeader("TERMINATE PROCESS");

    printf("[Action] Terminating Process %d (The middle one)...\n", pidB);
    terminateProcess(pidB);

    // CHECK 1: Did the count decrease?
    count = getprocessTableCount();
    if(count == 2) {
        printf("[PASS] Counter decreased to 2.\n");
    } else {
        printf("[FAIL] Counter is %d (Expected 2).\n", count);
    }

    // CHECK 2: Is Process B actually gone?
    printf("[Action] Trying to find Process %d again...\n", pidB);
    changeProcessState(pidB); // Should print "not found"

    // CHECK 3: Did Process C (the last one) survive the shift?
    printf("[Action] Checking Process %d (Should still exist)...\n", pidC);
    changeProcessState(pidC); // Should work successfully (NEW -> READY)

    printf("\n================================================\n");
    printf("              TESTING COMPLETE\n");
    printf("================================================\n");

    return 0;
}*/