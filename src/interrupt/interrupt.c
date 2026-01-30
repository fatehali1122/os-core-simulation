#include "interrupt.h"
#include <stdio.h>
#include <time.h>

#define Maximum_Interrupts 64

//Ring buffer storage attributes
static InterruptEvent queue[Maximum_Interrupts];
static int head = 0;
static int tail = 0;
static int count = 0;

static interruptStateStub stateStub = NULL;

int interruptInit(void) {

	head = tail = count = 0;
	stateStub = NULL;

	return 0;	
}

int interruptIsEmpty(void) {
	return (count == 0); 
}

int interruptIsFull(void) {
	return (count == Maximum_Interrupts);	
}

void interruptRegisterStateStub(interruptStateStub stub) {
	stateStub = stub;
}

int interruptRaise(InterruptType type, int pid, int data) {
	
	if(interruptIsFull()) {
		return -1;
	}
	queue[tail].type = type;
	queue[tail].pid = pid;
	queue[tail].data = data;
	queue[tail].timeStamp = time(NULL);
	
	tail = (tail + 1) % Maximum_Interrupts;
	count++;
		
	return 0;
}

int interruptFetch(InterruptEvent *event) {
	if(interruptIsEmpty() || event == NULL) {
		return -1;
	}
	*event = queue[head];
	head = (head + 1) % Maximum_Interrupts;
	count--;
		
	return 0;
}

void interruptHandle(const InterruptEvent *event) {
	if(!event) {
		return;
	}
	printf("[INTERRUPT] type = %d, pid = %d, time = %lld\n", event->type, event->pid, (long long) event->timeStamp);
	if(stateStub) {
		stateStub(event->type, event->pid, event->data);
	}
	
}