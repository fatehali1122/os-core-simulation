#include <stdio.h>
#include "interrupt.h"

/* Stub simulating process/scheduler reaction */
void testInterruptStub(InterruptType type, int pid, int data) {
	switch (type) {
		case INTERRUPT_TIMER:
			printf("[STUB] TIMER interrupt received for PID %d\n", pid);
			break;

		case INTERRUPT_IO:
			printf("[STUB] IO interrupt received for PID %d (data = %d)\n",
			       pid, data);
			break;

		case INTERRUPT_SYSCALL:
			printf("[STUB] SYSCALL interrupt received for PID %d\n", pid);
			break;

		default:
			printf("[STUB] UNKNOWN interrupt\n");
	}
}

int main(void) {
	InterruptEvent event;

	printf("=== Interrupt Module Test ===\n");

	/* Initialize interrupt subsystem */
	interruptInit();

	/* Register stub */
	interruptRegisterStateStub(testInterruptStub);

	/* Raise interrupts */
	interruptRaise(INTERRUPT_TIMER,   1, 0);
	interruptRaise(INTERRUPT_IO,      2, 128);
	interruptRaise(INTERRUPT_SYSCALL, 3, 0);
	interruptRaise(INTERRUPT_TIMER,   4, 0);

	/* Process interrupts */
	while (!interruptIsEmpty()) {
		if (interruptFetch(&event) == 0) {
			interruptHandle(&event);
		}
	}

	printf("=== All interrupts processed ===\n");
	return 0;
}
