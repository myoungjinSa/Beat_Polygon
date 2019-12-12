#include "stdafx.h"
#include "Timer.h"

std::chrono::steady_clock::time_point Timer::musicStartTime = std::chrono::steady_clock::now();
Timer::Timer()
{
}

Timer::~Timer()
{

}

void Timer::Start()
{
	startTime = std::chrono::steady_clock::now();
	elapsedTime = startTime;
	bStopped = false;
}


void Timer::Stop()
{
	bStopped = true;
}

float Timer::GetTimeElapsed()
{
	return fTimeElapsed;
}

void Timer::Tick(float fLockFps)
{
	
	std::chrono::steady_clock::time_point currTime = std::chrono::steady_clock::now();

	//std::chrono::steady_clock::time_point elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - elapsedTime)

	std::chrono::milliseconds milli = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - elapsedTime);
	std::chrono::duration<float> t = milli;

	elapsedTime = currTime;
	fTimeElapsed = t.count();


	//std::cout << t.c.count() << std::endl;
}

