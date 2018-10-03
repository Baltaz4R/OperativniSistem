#ifndef H_KERNEV_H_
#define H_KERNEV_H_

#include "PCB.h"
#include "IVTEntry.h"

typedef unsigned char IVTNo;

class IVTEntry;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void wait ();
	void signal();

	PCB* myPCB;
	IVTEntry* myEntry;
};



#endif /* H_KERNEV_H_ */
