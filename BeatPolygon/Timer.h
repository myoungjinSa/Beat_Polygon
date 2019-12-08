#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

	void Tick(float fLockFps = 0.0f);

	void Start();
	void Stop();
	void Reset();

	float GetTimeElapsed();

private:
	float fTimeElapsed;
//	std::chrono::duration<float, std::chrono::milliseconds> fMilli;
	
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point elapsedTime;


	bool bStopped;
	
};
