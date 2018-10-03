#include "IVTEntry.h"

int IVTEntry::init = 0;
IVTEntry** IVTEntry::allEntry = 0;
pInterrupt* IVTEntry::intr = 0;

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt pIntr) {
	if(init == 0) {
		init = 1;
		allEntry = new IVTEntry*[256];
		intr = new pInterrupt[256];
	}

	this->ivtNo = ivtNo;

	allEntry[(int) ivtNo] = this;
	intr[(int) ivtNo] = pIntr;

	oldIntr = 0;
	myEvent = 0;
}

IVTEntry::~IVTEntry() {
	myEvent = 0;
	oldIntr = 0;
	ivtNo = 0;
}

IVTEntry* IVTEntry::getEntry(IVTNo ivtNo) {
	return allEntry[(int) ivtNo];
}

