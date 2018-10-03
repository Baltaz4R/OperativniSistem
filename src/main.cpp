#include <iostream.h>
#include <dos.h>

#include "PCB.h"
#include "thread.h"
#include "timer.h"
#include "event.h"
#include "semaphor.h"
#include "idle.h"

int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]) {

	PCB* main = new PCB(0, 2, 4096);
	main->status = RUNNING;
	PCB::running = main;


	Timer* t = new Timer();

	int value = userMain(argc, argv);

	delete t;

	return value;

}
