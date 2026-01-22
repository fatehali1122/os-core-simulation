/*#include <stdio.h>
#include "process.h"     //Linkage

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
}*/
