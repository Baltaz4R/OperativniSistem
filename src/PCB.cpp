#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.h"
#include "queue.h"
#include "timer.h"

volatile Idle* PCB::idle = new Idle();
volatile PCB* PCB::running = 0;

void PCB::createStack(unsigned stackSize) {
	//if(stackSize > 65535) stackSize = 65535;  // maksimalna velicina steka je 64KB
	stackSize /= sizeof(unsigned);   // stackSize je bajtovima, posto je unsigned 2 bajta ovo je broj indeksa
	st = new unsigned[stackSize];
	#ifndef BCC_BLOCK_IGNORE
	//st[stackSize - 1] = FP_SEG(myThread);  // Postavljamo parametar funkcije
	//st[stackSize - 2] = FP_OFF(myThread);
	st[stackSize - 5] = 0x200;  // Postavljamo PSW, 10000...000 -I fleg enable-ovan
	st[stackSize - 6] = FP_SEG(PCB::wrapper);  // Postavljamo CS od PC-a
	st[stackSize - 7] = FP_OFF(PCB::wrapper);  // Postavljamo IP od PC-a
	// od -1 do -16 kontekst procesa
	ss = FP_SEG(st + stackSize - 16);  
	sp = FP_OFF(st + stackSize - 16);
	bp = sp;  //po pravilu BP se na pocetku stavlja da pokazuje na SP
	#endif
}

PCB::PCB(Thread *th, unsigned int t, unsigned stacksize) {
	time = t;
	myThread = th;
	createStack(stacksize);
	status = NEW;
	waiting = new Queue();
}

PCB::~PCB() {
	delete [] st;
	//delete myThread;
	delete waiting;
}

void PCB::start() {
	lock;
	if (status == NEW) {
		status = READY;
		Scheduler::put(this);
	}
	unlock;
}

void PCB::waitToComplete() {
	lock;
	if (status != DONE && status != NEW && running != this) {
		running->status = BLOCK;
		((Queue*) waiting)->enque((PCB*) running);
		unlock;
		Timer::dispatch();
	} else {
		unlock;
	}
}

void PCB::wrapper(){
	running->myThread->run();
	lock;
	running->status = DONE;
	while(((Queue*) running->waiting)->size() > 0) {
		PCB* temp = ((Queue*) running->waiting)->deque();
		temp->status = READY;
		Scheduler::put(temp);
	}
	unlock;
	Timer::dispatch();
}

void PCB::setIdle() {
	running = idle->myPCB;
}
