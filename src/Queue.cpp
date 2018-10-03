#include "queue.h"

void Queue::enque(PCB* pcb) {
	Elem *temp = new Elem(pcb);
	s++;
	if(head == 0){
		head = temp;
		tail = head;
	} else {
		tail->next = temp;
		tail = tail->next;
    }
	temp = 0;
}

void Queue::deque(PCB* pcb) {
	Elem* temp = head;
	Elem* p = 0;
	while (temp){
		if (temp->pcb != pcb){
			p = temp;
			temp = temp->next;
		} else {
			if(!p) {
				head = temp->next;
				if (!temp->next) tail = head; 
			} else {
				p->next = temp->next;
				if (!temp->next) tail = p; 
			}
			delete temp->pcb;
			delete temp;
			temp = 0;
			s--;
		}
	}
}

int Queue::size() {
	return s;
}

PCB* Queue::deque() {
	Elem* temp = head;
	if (head != 0){
		if (head != tail) {
			head = head->next;
		} else {
			head = tail = 0;
		}
		s--;
		return temp->pcb;
		delete temp;
	} else {
		return 0;
	}

}

Queue::~Queue() {
	while(head) {
		Elem* temp = head;
		head = head->next;
		delete temp->pcb;
		delete temp;
	}
	s = 0;
}
