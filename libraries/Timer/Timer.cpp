/*
 
Autor 	Alex Krieg
Datum  	30.4.2017
Version 1.0

*/



#include "Timer.h"

Timer::Timer()
{
	isRunning = 0;
}
Timer::~Timer()
{
	
}
bool Timer::start(unsigned long intervallMS)
{
	if(isRunning)
	{
		runningTime = clock();
		if((runningTime - startTime) > intervallMS)
		{
			isRunning = 0;
			return 1;
		}
		
	}
	else
	{
		isRunning 	= 1;
		startTime 	= clock();
		runningTime = clock();
	}
	return 0;
}
unsigned long Timer::getRuntime()
{
	if(isRunning)
	{
		return runningTime - startTime;
	}
	return 0;
}
void Timer::stop()
{
	isRunning = 0;
}