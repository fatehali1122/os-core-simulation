#ifndef SYSCALL_H
#define SYSCALL_H

#include "interrupt.h"
//Initializes all Modules
void sys_init(void);

//Process syscalls
int sys_create_process(int priority,int burstTime,int memoryUsage);
int sys_terminate_process(int pid);
int sys_get_process_list(void);

//Memory syscalls
int sys_allocate_memory(int pid,int size,int strategy);
int sys_deallocate_memory(int pid);
int sys_get_memory_map(void);

//Interrupt Handler and hardware triggers
void sys_interrupt_handler(InterruptType type, int pid, int data);
int sys_scheduler_timer(int pid);
int sys_io_request(int pid);
void sys_execute_interrupts(void);

//Filesystem syscalls
int sys_create_file(const char* name,int permissions);
int sys_write_file(const char* name,const char* data);
int sys_read_file(const char* name);
int sys_delete_file(const char* name);
void sys_list_files(void);

//added initializer
void fs_init(void);

#endif