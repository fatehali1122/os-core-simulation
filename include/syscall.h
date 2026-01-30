#ifndef SYSCALL_H
#define SYSCALL_H

//Initializes all Modules
void sys_init(void);

//Process syscalls
int sys_create_process(int priority,int burstTime,int memoryUsage);
int sys_terminate_process(int pid);
int sys_get_process_list(void);
int sys_change_process_state(int pid);

//Memory syscalls
int sys_allocate_memory(int pid,int size,int strategy);
int sys_deallocate_memory(int pid);
int sys_get_memory_map(void);

//Filesystem syscalls
int sys_create_file(const char* name,int permissions);
int sys_write_file(const char* name,const char* data);
int sys_read_file(const char* name);
int sys_delete_file(const char* name);
void sys_list_files(void);

//added initlizer
void fs_init(void);

#endif