#ifndef H_EVENT_H_
#define H_EVENT_H_

#include "PCB.h"
#include "IVTEntry.h"

typedef unsigned char IVTNo;


// Makro
#define PREPAREENTRY(numEntry, callOld)\
	void interrupt inter##numEntry(...);\
	IVTEntry* newEntry##numEntry = new IVTEntry(numEntry, inter##numEntry);\
	void interrupt inter##numEntry(...) {\
		newEntry##numEntry->myEvent->signal();\
		if (callOld == 1) newEntry##numEntry->oldIntr();\
	}

class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};


#endif /* H_EVENT_H_ */
