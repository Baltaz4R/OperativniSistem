#include <dos.h>
#include "KernEv.h"
#include "timer.h"
#include "SCHEDULE.h"


KernelEv::KernelEv(IVTNo ivtNo) {
	myPCB = (PCB*) PCB::running;
	myEntry = IVTEntry::allEntry[(int) ivtNo];
	myEntry->myEvent = this;

	#ifndef BCC_BLOCK_IGNORE
	myEntry->oldIntr = getvect((int) ivtNo);
	setvect((int) ivtNo, IVTEntry::intr[(int) ivtNo]);
	#endif
}

KernelEv::~KernelEv() {
	#ifndef BCC_BLOCK_IGNORE
	setvect((int) myEntry->ivtNo, myEntry->oldIntr);
	#endif

	IVTEntry::allEntry[(int) myEntry->ivtNo] = 0;
	IVTEntry::intr[(int) myEntry->ivtNo] = 0;
	delete myEntry;
	myEntry = 0;
	myPCB = 0;
}

void KernelEv::wait(){
	lock;
	if (PCB::running == myPCB) {
		PCB::running->status = BLOCK;
		unlock;
		Timer::dispatch();
	} else {
		unlock;
	}
}

void KernelEv::signal(){
	lock;
	myPCB->status = READY;
	Scheduler::put(myPCB);
	unlock;
	Timer::dispatch();
}

