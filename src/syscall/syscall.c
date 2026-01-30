#include <stdio.h>
#include <string.h>

#include "syscall.h"
#include "process.h"
#include "process_scheduler.h"
#include "memory.h"
#include "file_system.h"
#include "interrupt.h"

static int is_valid_pid(int pid)
{
    if(!processExists(pid))
    {
        printf("PID %d does not exist ",pid);
        return 0;
    }
    return 1;
}

static int is_valid_filename(const char *name)
{
    if(!name || strlen(name) == 0 || strlen(name) >= 32)
    {
        printf("Invalid file name\n");
        return 0;
    }
    return 1;
}

void sys_init(void)
{
    sched_init();          //scheduler file
    initializeMemory();    //Memory file
    fs_init();
	interruptInit();		//interrupts initialized
    printf("System Initialized via system call\n");
}

int sys_create_process(int priority,int burstTime,int memSize)
{
    int pid = processCreation(priority,burstTime,memSize);
    if(pid == -1)
    {
        return -1;
    }

    int addr = allocateMemory(pid,memSize,STRATEGY_FIRST_FIT);
    if(addr == -1)
    {
        terminateProcess(pid);
        return -1;
    }
	
	processAdmit(pid);
    return pid;
}

int sys_terminate_process(int pid)
{
    if(!is_valid_pid(pid))
    {
        return -1;
    }

    terminateProcess(pid);
    deallocateMemory(pid);

    return 0;
}

int sys_allocate_memory(int pid,int size,int strategy)
{
    if(!is_valid_pid(pid) || size <= 0)
    {
        return -1;
    }

    return allocateMemory(pid,size,strategy);
}

int sys_deallocate_memory(int pid)
{
    if(!is_valid_pid(pid))
    {
        return -1;
    }

    deallocateMemory(pid);
    return 0;
}

int sys_create_file(const char* name,int permissions)
{
    if(!is_valid_filename(name))
    {
        return -1;
    }
    return fs_createFile(name,permissions);
}

int sys_write_file(const char* name,const char* data)
{
    if(!is_valid_filename(name) || !data)
    {
        return -1;
    }
    return fs_writeFile(name,data);
}

int sys_read_file(const char* name)
{
    if(!is_valid_filename(name))
    {
        return -1;
    }
    return fs_readFile(name);
}

int sys_delete_file(const char* name)
{
    if(!is_valid_filename(name))
    {
        return -1;
    }
    return fs_deleteFile(name);
}

void sys_list_files(void)
{
    fs_listFiles();
}

int sys_get_process_list(void)
{
    struct Node* temp = getProcessHead();
    if (!temp) {
        printf("No processes exist.\n");
        return -1;
    }

    printf("\nPID   PRIO  BURST  STATE\n");
    printf("----------------------------\n");

    while (temp != NULL) {
        printf("%-5d %-5d %-5d  %s\n",
               temp->pcb.pid,
               temp->pcb.priority,
               temp->pcb.burstTime,
               getStateString(temp->pcb.status));
        temp = temp->next;
    }
    return 0;
}

int sys_get_memory_map(void)
{
    printMemoryMap();          
    printFragmentationStats(); 
    return 0;
}
//hardware triggers
int sys_scheduler_timer(int pid) {
	
	if(!processExists(pid)){
		return -1;
	}
	return interruptRaise(INTERRUPT_TIMER, pid, 0);
	
}
int sys_io_request(int pid) {
	
	if(!processExists(pid)){
		return -1;
	}
	return interruptRaise(INTERRUPT_IO, pid, 0);
	
}
//handler for interrupts via system calls
void sys_interrupt_handler(InterruptType type, int pid, int data) {
	
	(void)data;
	switch(type) {
		
		case INTERRUPT_TIMER:
			processPreempt(pid);
			break;
			
		case INTERRUPT_IO:
			processBlock(pid);
			break;
			
		case INTERRUPT_SYSCALL:
			printf("[SYSTEM_INTERRUPT] System Call requested.\n");
			break;
			
		default:
			printf("Unknown Interrupt Type\n");
				
	}
		
}

void sys_execute_interrupts(void) {
	
	InterruptEvent event;
	
	while (interruptFetch(&event) == 0) {
		interruptHandle(&event);
	}
	
}