#ifndef H_IDLE_H_
#define H_IDLE_H_

#include "thread.h"

class Thread;

class Idle: public Thread {
public:
	Idle();
	virtual void run();
	void start();
};



#endif /* H_IDLE_H_ */
