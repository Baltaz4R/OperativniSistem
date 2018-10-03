#ifndef H_TIMER_H_
#define H_TIMER_H_


class Timer {
public:
	Timer();
	~Timer();

	static volatile int context_switch;
	static volatile unsigned int lockFlag;

	static void dispatch();
	static void sleep(Time timeToSleep);

	//Inicijalizacija i restauracija tajmerske rutine
	static void inic();
	static void restore();
};

#endif
