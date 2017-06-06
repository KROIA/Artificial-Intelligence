/*
 
Autor 	Alex Krieg
Datum  	30.4.2017
Version 1.0

*/



#ifndef TIMER
#define TIMER
#include <ctime>
#include <stdio.h>

class Timer
{
	public:
	Timer();
	~Timer();
	bool start(unsigned long intervallMS);
	unsigned long getRuntime();
	void stop();
	private:
	clock_t startTime;
	clock_t runningTime;
	bool isRunning;
};
#endif

