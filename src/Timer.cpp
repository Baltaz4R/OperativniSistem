#include <dos.h>
#include "squeue.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include "timer.h"

volatile unsigned long counter = 20;

volatile SQueue* SleepQueue = new SQueue();

volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;

volatile int Timer::context_switch = 0;
volatile unsigned int Timer::lockFlag = 1;

void tick();

unsigned oldTimerOFF, oldTimerSEG;

Timer::Timer() {
	inic();
	//pocetnu nit
}

Timer::~Timer() {
	restore();
	delete PCB::idle;
	//delete pocetnu nit
}

void interrupt timer() {  // prekidna rutina koja se poziva na svakih 55ms

	if (!Timer::context_switch) {
		counter--;
		((SQueue*) SleepQueue)->deque();  // budjenje uspavanih niti
	}
	if (counter == 0 || Timer::context_switch) {
		if (Timer::lockFlag) {

			Timer::context_switch = 0;
			#ifndef BCC_BLOCK_IGNORE
			asm {
					mov tsp, sp  // prebacujemo menjan stek
					mov tss, ss
					mov tbp, bp
			}
			#endif
			PCB::running->sp = tsp;  // cuvamo stek
			PCB::running->ss = tss;
			PCB::running->bp = tbp;

			if(PCB::running->status == RUNNING) {
				PCB::running->status = READY;
				Scheduler::put((PCB*)PCB::running);
			}

			PCB::running = Scheduler::get();	// Scheduler
			if (PCB::running == 0)
				PCB::setIdle();
			else
				PCB::running->status = RUNNING;

			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;

			counter = PCB::running->time;

			#ifndef BCC_BLOCK_IGNORE
			asm {
					mov sp, tsp
					mov ss, tss
					mov bp, tbp
			}
			#endif
		}
		else Timer::context_switch = 1;
	}
	if (!Timer::context_switch) {
		tick(); 	// receno u tekstu zadatka
		#ifndef BCC_BLOCK_IGNORE
		asm int 60h;  	//poziv prekidne rutine koja se nalazi na 60h
		#endif
	}
}

void Timer::dispatch() {
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	#endif
	context_switch = 1;
	#ifndef BCC_BLOCK_IGNORE
	asm int 8h;
	asm sti;
	#endif
}

void Timer::sleep(Time timeToSleep) {
	if(timeToSleep == 0)
			return;
	lock;
	PCB::running->status = BLOCK;
	((SQueue*) SleepQueue)->enque((PCB*)PCB::running, (unsigned long) timeToSleep);
	unlock;
	Timer::dispatch();
}

// postavlja novu prekidnu rutinu
void Timer::inic() {
#ifndef BCC_BLOCK_IGNORE
	asm{
		cli
		push es
		push ax

		mov ax,0   //  ; inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //; pamti staru rutinu
		mov word ptr oldTimerSEG, ax	
		mov ax, word ptr es:0020h	
		mov word ptr oldTimerOFF, ax	

		mov word ptr es:0022h, seg timer	 //postavlja
		mov word ptr es:0020h, offset timer //novu rutinu

		mov ax, oldTimerSEG	 //	postavlja staru rutinu	
		mov word ptr es:0182h, ax //; na int 60h
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

// vraca staru prekidnu rutinu
void Timer::restore() {
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}
