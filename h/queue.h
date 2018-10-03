#ifndef H_QUEUE_H_
#define H_QUEUE_H_

#include "PCB.h"

class Queue {
private:
	struct Elem {
		PCB* pcb;
		Elem* next;
		Elem (PCB* Pcb){
			pcb = Pcb;
			next = 0;
		}
	} *head, *tail;
	int s;
		
public:
	Queue() {
		head = 0; 
		tail = 0; 
		s = 0;
	}
	~Queue();
	void enque(PCB* pcb);
	void deque(PCB* pcb);
	PCB* deque();
	int size();
};


#endif
