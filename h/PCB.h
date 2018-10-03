#ifndef H_PCB_H_
#define H_PCB_H_

#include "thread.h"
#include "queue.h"
#include "idle.h"

#define lock; Timer::lockFlag = 0;
#define unlock; Timer::lockFlag = 1;\
if (Timer::context_switch) dispatch();

class Queue;

enum Status{NEW, DONE, RUNNING, BLOCK, READY};

class PCB{
public:
	unsigned* st;
	volatile unsigned sp;
	volatile unsigned ss;
	volatile unsigned bp;
	volatile unsigned time;  // koliko dugo se nit izvrsava
	volatile Status status;

	Thread* myThread;
	volatile Queue* waiting;  // red niti koje cekaju da se zavrsi ova nit
	
	volatile static PCB* running;
	volatile static Idle* idle;

	static void setIdle();

	void start();
	void waitToComplete();
	PCB(Thread *th, unsigned int t, unsigned stacksize);
	void createStack(unsigned stackSize);
	~PCB();
	static void wrapper();
};

#endif
