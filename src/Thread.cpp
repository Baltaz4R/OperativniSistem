#include "thread.h"
#include "timer.h"
#include "queue.h"
#include "SCHEDULE.H"

//volatile Queue* PCBQueue = new Queue();

Thread::Thread (StackSize stackSize, Time timeSlice) {
	lock;
	myPCB = new PCB(this, timeSlice, stackSize);
	//((Queue*) PCBQueue)->enque(myPCB);
	unlock;
}

Thread::~Thread() {
	lock;
	//((Queue*) PCBQueue)->deque(myPCB);
	delete myPCB;
	myPCB = 0;
	unlock;
}

void Thread::waitToComplete() {
	myPCB->waitToComplete();
}

void Thread::start() {
	myPCB->start();
}

void dispatch() {
	Timer::dispatch();
}

void Thread::sleep(Time timeToSleep) {
	Timer::sleep(timeToSleep);
}

