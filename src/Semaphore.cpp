#include "semaphor.h"
#include "PCB.h"
#include "KernSem.h"
#include "timer.h"

Semaphore::Semaphore(int init) {
	lock;
	myImpl = new KernelSem(init);
	unlock;
}

Semaphore::~Semaphore() {
	lock;
	delete myImpl;
	unlock;
}

int Semaphore::wait(int toBlock) {
	return myImpl->wait(toBlock);
}

void Semaphore::signal() {
	myImpl->signal();
}

int Semaphore::val () const {
	return myImpl->val();
}

