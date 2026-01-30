#include <stdio.h>
#include <stdlib.h>
#include "../../include/memory.h"

static struct MemoryBlock memoryTable[MAX_BLOCKS];
static int blockCount = 0; 

void initializeMemory(void) {
    memoryTable[0].startAddress = 0;
    memoryTable[0].size = TOTAL_MEMORY_SIZE;
    memoryTable[0].pid = 0; 
    memoryTable[0].isFree = 1; 
    
    blockCount = 1; 
    printf("Memory System Initialized (%d bytes)\n", TOTAL_MEMORY_SIZE);
}


int findBlockIndex(int size, int strategy) {
    int targetIndex = -1;
    
    if (strategy == STRATEGY_FIRST_FIT) {
        // Find the first free block that fits
        for (int i = 0; i < blockCount; i++) {
            if (memoryTable[i].isFree && memoryTable[i].size >= size) {
                return i; 
            }
        }
    } 
    else if (strategy == STRATEGY_BEST_FIT) {
        // Find smallest free block that fits to save space
        int minSize = TOTAL_MEMORY_SIZE + 1;
        for (int i = 0; i < blockCount; i++) {
            if (memoryTable[i].isFree && memoryTable[i].size >= size) {
                if (memoryTable[i].size < minSize) {
                    minSize = memoryTable[i].size;
                    targetIndex = i;
                }
            }
        }
    } 
    else if (strategy == STRATEGY_WORST_FIT) {
        // Find largest free block that fits
        int maxSize = -1;
        for (int i = 0; i < blockCount; i++) {
            if (memoryTable[i].isFree && memoryTable[i].size >= size) {
                if (memoryTable[i].size > maxSize) {
                    maxSize = memoryTable[i].size;
                    targetIndex = i;
                }
            }
        }
    }
    
    return targetIndex;
}

int allocateMemory(int pid, int size, int strategy) {
    if (size <= 0) {
        fprintf(stderr, "Error: Invalid memory size requested.\n");
        return -1;
    }

    int index = findBlockIndex(size, strategy);

    if (index == -1) {
        fprintf(stderr, "Error: Not enough memory (Allocation Failed for PID %d)\n", pid);
        return -1;
    }

    // Check if we need to split the block
    if (memoryTable[index].size == size) {
        memoryTable[index].isFree = 0;
        memoryTable[index].pid = pid;
        return memoryTable[index].startAddress;
    } 
    else {
        // Check if array has space for a new block entry
        if (blockCount >= MAX_BLOCKS) {
            fprintf(stderr, "Error: Memory Table Full (Too many fragments)\n");
            return -1;
        }

        // Shift all subsequent blocks to the right to make space for the new split
        for (int i = blockCount; i > index + 1; i--) {
            memoryTable[i] = memoryTable[i-1];
        }

        // Create the new free block
        memoryTable[index+1].startAddress = memoryTable[index].startAddress + size;
        memoryTable[index+1].size = memoryTable[index].size - size;
        memoryTable[index+1].pid = 0;
        memoryTable[index+1].isFree = 1;

        // Update the current block to be the Allocated one
        memoryTable[index].size = size;
        memoryTable[index].pid = pid;
        memoryTable[index].isFree = 0;

        blockCount++; // We added a new block to the list
        return memoryTable[index].startAddress;
    }
}

// This function merges adjacent free blocks to reduce fragmentation
void mergeFreeBlocks(void) {
    for (int i = 0; i < blockCount - 1; i++) {
        // If current and next are both free, merge them
        if (memoryTable[i].isFree && memoryTable[i+1].isFree) {
            // Add size of next to current
            memoryTable[i].size += memoryTable[i+1].size;

            // Shift everything left to delete the [i+1] entry
            for (int j = i + 1; j < blockCount - 1; j++) {
                memoryTable[j] = memoryTable[j+1];
            }
            
            blockCount--;
            i--; 
        }
    }
}

void deallocateMemory(int pid) {
    int freed = 0;
    for (int i = 0; i < blockCount; i++) {
        if (memoryTable[i].pid == pid && !memoryTable[i].isFree) {
            memoryTable[i].isFree = 1;
            memoryTable[i].pid = 0;
            freed = 1;
        }
    }

    if (freed) {
        printf("Memory released for PID %d.\n", pid);
        mergeFreeBlocks(); 
    } else {
        printf("Warning: No memory found for PID %d to release.\n", pid);
    }
}

// Calculates Internal and External Fragmentation
void printFragmentationStats(void) {
    int totalFree = 0;
    int largestBlock = 0;
    
    for (int i = 0; i < blockCount; i++) {
        if (memoryTable[i].isFree) {
            totalFree += memoryTable[i].size;
            if (memoryTable[i].size > largestBlock) {
                largestBlock = memoryTable[i].size;
            }
        }
    }

    int extFrag = totalFree - largestBlock;

    int intFrag = 0; 

    printf("--- Fragmentation Stats ---\n");
    printf("Total Free Memory: %d\n", totalFree);
    printf("Largest Usable Block: %d\n", largestBlock);
    printf("External Fragmentation: %d\n", extFrag);
    printf("Internal Fragmentation: %d (Variable Partitioning)\n", intFrag);
}

void printMemoryMap(void) {
    printf("\n[MEMORY MAP] Count: %d blocks\n", blockCount);
    printf("| Start |  End  | Size | PID | Status |\n");
    printf("|-------|-------|------|-----|--------|\n");
    
    for (int i = 0; i < blockCount; i++) {
        printf("| %-5d | %-5d | %-4d | %-3d | %s |\n", 
            memoryTable[i].startAddress,
            memoryTable[i].startAddress + memoryTable[i].size,
            memoryTable[i].size,
            memoryTable[i].pid,
            memoryTable[i].isFree ? "FREE" : "USED");
    }
    printf("---------------------------------------\n");
}