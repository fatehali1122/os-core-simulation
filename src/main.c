#include <stdio.h>
#include "memory_manager.h"     //Linkage

// This is a temporary main function to test the build system
int main() {
    printf("------Before executing-----\n");
    printf("Counter: %d\n",getprocessTableCount());
    int processId = processCreation(1,1,1);
    printf("Process ID: %d \n", processId);

    printf("------After executing-----\n");
    printf("Counter: %d\n",getprocessTableCount());

    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);
    changeProcessState(1);

    terminateProcess(1);
    return 0;
}