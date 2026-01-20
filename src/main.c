#include <stdio.h>
#include "memory_manager.h"     //Linkage

// This is a temporary main function to test the build system
int main() {
    int result = processCreation(1,1,1);
    printf("%d \n",result);

    changeProcessState(1);

    terminateProcess(1);
    
    return 0;
}