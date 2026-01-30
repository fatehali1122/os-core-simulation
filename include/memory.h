#ifndef MEMORY_H
#define MEMORY_H

// Using a fixed size for the main memory
#define TOTAL_MEMORY_SIZE 1024 
// Maximum number of blocks 
#define MAX_BLOCKS 100 

#define STRATEGY_FIRST_FIT 1
#define STRATEGY_BEST_FIT 2
#define STRATEGY_WORST_FIT 3


struct MemoryBlock {
    int startAddress;
    int size;
    int pid;
    int isFree;   
};


void initializeMemory(void);


int allocateMemory(int pid, int size, int strategy);

// Frees all memory blocks owned by a specific PID and merges free blocks
void deallocateMemory(int pid);

void printMemoryMap(void);


void printFragmentationStats(void);

#endif