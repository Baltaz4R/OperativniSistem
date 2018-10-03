#include <dos.h>
#include "KernSem.h"
#include "PCB.h"
#include "SCHEDULE.h"
#include "timer.h"
#include "queue.h"


KernelSem::KernelSem(int init) {
	value = init;
	BlockQueue = new Queue();
}

KernelSem::~KernelSem() {
	delete BlockQueue;
}

int KernelSem::wait (int toBlock) {
	lock;
	value--;
	if(value < 0) {
		if(toBlock) {
			PCB::running->status = BLOCK;
			BlockQueue->enque((PCB*) PCB::running);
			unlock;
			Timer::dispatch();
			return 1;
		} else {
			value++;
			unlock;
			return -1;
		}
	}
	unlock;
	return 0;
}

void KernelSem::signal() {
	lock;
	if(value < 0 && BlockQueue->size() > 0) {
		PCB* temp = BlockQueue->deque();
		temp->status = READY;
		Scheduler::put(temp);
	}
	value++;
	unlock;
}

int KernelSem::val() const {
	return value;
}

