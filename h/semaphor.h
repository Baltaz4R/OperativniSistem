#ifndef H_SEMAPHOR_H_
#define H_SEMAPHOR_H_

class KernelSem;

class Semaphore {
public:
	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual int wait (int toBlock);
	virtual void signal();
	int val () const; // Returns the current value of the semaphore
private:
	KernelSem* myImpl;
};

#endif /* H_SEMAPHOR_H_ */
