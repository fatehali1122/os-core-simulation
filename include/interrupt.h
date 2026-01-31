/*Instructions:

-This simulation does not modify the process state explicitly
-It communicates directly with systemcalls through triggered interrupts
-No dependency is required for process/memory module 

*/
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <time.h>

typedef enum {
	INTERRUPT_TIMER,
	INTERRUPT_IO,
	INTERRUPT_SYSCALL
}InterruptType;

typedef struct {
	InterruptType type;
	int pid;
	int data;
	time_t timeStamp;	
}InterruptEvent;

int interruptInit(void);
int interruptRaise(InterruptType type, int pid, int data);
int interruptFetch(InterruptEvent *event);
void interruptHandle(const InterruptEvent *event);

int interruptIsEmpty(void);
int interruptIsFull(void);

#endif