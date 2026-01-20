#include <stdio.h>
#include "memory_manager.h"     //Linkage

// This is a temporary main function to test the build system
int main() {
    int processId = processCreation(1,1,1);
    printf("Process ID: %d \n", processId);

    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);

    terminateProcess(1);
	
    
    return 0;
}