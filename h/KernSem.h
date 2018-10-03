#ifndef H_KERNSEM_H_
#define H_KERNSEM_H_

#include "queue.h"

class KernelSem {
public:
	KernelSem(int init=1);
	~KernelSem();
	void signal();
	int wait(int toBlock);
	int val() const;
private:
	int value;
	Queue* BlockQueue;
};



#endif /* H_KERNSEM_H_ */
