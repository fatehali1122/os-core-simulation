#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../include/process.h"

static int processIdCount = 0;
static struct Node* head = NULL;
static struct Node* tail = NULL;

static struct Node* findNodeInternal(int pid, struct Node** prevNode) {
    struct Node* curr = head;
    struct Node* prev = NULL;
    while (curr) {
        if (curr->pcb.pid == pid) {
            if (prevNode) *prevNode = prev;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

static int generateSafePid(void) {
    if (processIdCount < INT_MAX) {
        return ++processIdCount;
    }
    int candidate = 1;
    while (candidate < INT_MAX) {
        struct Node* temp = head;
        int used = 0;
        while (temp) {
            if (temp->pcb.pid == candidate) {
                used = 1;
                break;
            }
            temp = temp->next;
        }
        if (!used) {
            processIdCount = candidate;
            return candidate;
        }
        candidate++;
    }
    return -1;
}

int processCreation(int priority, int burstTime, int memoryUsage) {
    if (priority < 0 || burstTime < 0 || memoryUsage < 0) {
        fprintf(stderr, "Error: Invalid definition parameters\n");
        return -1;
    }
    int pid = generateSafePid();
    if (pid == -1) {
        fprintf(stderr, "Error: Process ID pool exhausted\n");
        return -1;
    }
    struct Node* newNode = (struct Node*)calloc(1, sizeof(struct Node));
    if (!newNode) {
        fprintf(stderr, "Error: Heap allocation failed\n");
        return -1;
    }
    newNode->pcb.pid = pid;
    newNode->pcb.status = NEW;
    newNode->pcb.priority = priority;
    newNode->pcb.burstTime = burstTime;
    newNode->pcb.memoryUsage = memoryUsage;
    newNode->next = NULL;
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    return pid;
}

void changeProcessState(int pid) {
    struct Node* node = findNodeInternal(pid, NULL);
    if (!node) {
        printf("Process %d not found.\n", pid);
        return;
    }
    enum ProcessState currentStatus = node->pcb.status;
    enum ProcessState newStatus = currentStatus;
    const char* strOld = getStateString(currentStatus);
    switch (currentStatus) {
        case NEW:
            newStatus = READY;
            break;
        case READY:
            newStatus = RUNNING;
            break;
        case RUNNING:
            newStatus = WAITING;
            break;
        case WAITING:
            newStatus = READY;
            break;
        default:
            printf("INVALID STATE or Process already Terminated\n");
            return;
    }
    node->pcb.status = newStatus;
    printf("Status: %s --> %s\n", strOld, getStateString(newStatus));
}

void terminateProcess(int pid) {
    struct Node* prev = NULL;
    struct Node* node = findNodeInternal(pid, &prev);
    if (!node) {
        printf("Process %d not found.\n", pid);
        return;
    }
    if (node == head) {
        head = node->next;
        if (!head) {
            tail = NULL;
        }
    } else {
        prev->next = node->next;
        if (node == tail) {
            tail = prev;
        }
    }
    free(node);
    printf("Process %d Terminated & Memory freed.\n", pid);
}

const char* getStateString(enum ProcessState s) {
    switch (s) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case WAITING: return "WAITING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

struct Node* getProcessHead(void) {
    return head;
}