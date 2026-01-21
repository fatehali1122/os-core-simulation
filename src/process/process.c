#include <stdio.h>
#include <stdlib.h>
#include "process.h"           //Linkage

//linked list variables

static int processIdCount = 0;
struct Node* head = NULL;
struct Node* tail = NULL;

int processCreation(int priority, int burstTime, int memoryUsage) {
	
	struct Node* newNode = malloc(sizeof(struct Node));
	
	if(newNode == NULL) {
		
		printf("Error: Memory allocation failed or struct Node doesn't exist\n");
		return -1;
		
	}
	
	newNode->pcb.pid = ++processIdCount;
	newNode->pcb.status = NEW;
	newNode->pcb.priority = priority;
	newNode->pcb.burstTime = burstTime;
	newNode->pcb.memoryUsage = memoryUsage;
	
	newNode->next = NULL;
	
	if(head == NULL) {
		
		head = newNode;
		tail = newNode;
		
	}
	else {
		
		tail->next = newNode;
		tail = newNode;
		
	}
	
	return newNode->pcb.pid;
	
}

void changeProcessState(int pid) {
	
	struct Node* current = head;
	int found = 0;
	
	while(current != NULL) {
		
		if(current->pcb.pid == pid){
			
			found = 1;
			
			switch (current->pcb.status) {
				
				case NEW:
                current->pcb.status = READY;
                printf("Status: NEW --> READY\n");
                break;

                case READY:
                current->pcb.status = RUNNING;
                printf("Status: READY --> RUNNING\n");

                break;
                
                case RUNNING:
                current->pcb.status = WAITING;
                printf("Status: RUNNING --> WAITING\n");
                break;

                case WAITING:
                current->pcb.status = READY;
                printf("Status: WAITING --> READY\n");
                break;
                
                default:
                printf("INVALID STATE or Process already Terminated\n");
                break;				
			}
			break;			
		}
		
		current = current->next;
	}
	if(found == 0) {
		
		printf("Process %d not found.\n", pid);
		
	}
}

void terminateProcess(int pid) {
	
	struct Node* current = head;
	struct Node* previous = NULL;
	
	while(current != NULL) {
		
		if(current->pcb.pid == pid){
			
			//when pid is in head node
			if (current == head) {
				
				head = current->next;
				
				if (head == NULL) {
					
					tail = NULL;
					
				}
				
			}
			//when pid is in middle of the list or tail node
			else {
				
				previous->next = current->next;
				
				if (current == tail) {
					
					tail = previous;
					
				}
				
			}
			free(current);
			printf("Process %d Terminated & Memory freed.\n", pid);
			return;
						
		}
		
		previous = current;
		current = current->next;
		
	}
	
	printf("Process %d not found.\n", pid);
	
}

const char* getStateString(enum ProcessState s) {

    switch(s) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

struct Node* getProcessHead() {
    return head;
}