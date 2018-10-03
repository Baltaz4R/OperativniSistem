#ifndef H_IVTENTRY_H_
#define H_IVTENTRY_H_

#include "KernEv.h"

typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);

class KernelEv;

class IVTEntry {
public:
	IVTEntry(IVTNo ivtNo, pInterrupt pIntr);
	~IVTEntry();

	static IVTEntry** allEntry;
	static pInterrupt* intr;
	static IVTEntry* getEntry(IVTNo ivtNo);

	pInterrupt oldIntr;

	KernelEv* myEvent;

protected:
	friend class KernelEv;
private:
	IVTNo ivtNo;
	static int init;
};

#endif /* H_IVTENTRY_H_ */
