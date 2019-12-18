#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

	void Tick(const float& fLockFps = 0.0f);

	void Start();
	void Stop();
	
	const float GetTimeElapsed() const;


public:
	static std::chrono::steady_clock::time_point musicStartTime;
private:

	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point elapsedTime;

	float fTimeElapsed;
	bool bStopped;
	
};
