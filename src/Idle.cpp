#include "idle.h"
#include "pcb.h"

volatile int i = 1;

Idle::Idle(): Thread(defaultStackSize, 1) {}

void Idle::run() {
	while (i);
}
void Idle::start() {
	asm cli;
	/*if (myPCB->NEW) {
		myPCB->NEW = 0;
	}*/
	asm sti;
}


