#include <stdio.h>
#include "memory/memory_manager.h"     //Linkage

// This is a temporary main function to test the build system
int main() {
    int result = processCreation(1,1,1);
    printf("%d \n",result);

    changeProcessState(75);
    
    printf("Build successful! The OS Simulation is running.\n");
    return 0;
}