#ifndef H_SQUEUE_H_
#define H_SQUEUE_H_

#include "PCB.h"

class SQueue {
private:
	struct Elem {
		unsigned long time;
		PCB* pcb;
		Elem* next;
		Elem (PCB* Pcb, unsigned long t){
			pcb = Pcb;
			time = t;
			next = 0;
		}
	} *head;
public:
	SQueue() {
		head = 0;
	}
	~SQueue();
	void enque(PCB* pcb, unsigned long t);
	void deque();
};




#endif /* H_SQUEUE_H_ */
