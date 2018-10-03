#include "squeue.h"
#include "SCHEDULE.h"
#include "PCB.h"
#include "timer.h"

void SQueue::enque(PCB* pcb, unsigned long t) {
	if(head == 0) {
		Elem* temp = new Elem(pcb, t);
		head = temp;
	} else {
		Elem* temp = head;
		Elem* p = 0;
		while (temp->time < t) {
			t = t - temp->time;
			p = temp;
			temp = temp->next;
			if (!temp) break;
		}
		Elem* NEW = new Elem(pcb, t);
		if (p != 0) {
			p->next = NEW;
		} else {
			head = NEW;
			temp->time -= t;
		}
		NEW->next = temp;
    }
}

void SQueue::deque() {
	if (head) {
		head->time--;
		while (head->time == 0) {
			head->pcb->status = READY;
			Scheduler::put(head->pcb);
			Elem* temp = head;
			head = head->next;
			if (!head) break;
			delete temp;  // mozda je greska
		}
	}
}

SQueue::~SQueue() {
	while(head) {
		Elem* temp = head;
		head = head->next;
		delete temp->pcb;
		delete temp;
	}
}
