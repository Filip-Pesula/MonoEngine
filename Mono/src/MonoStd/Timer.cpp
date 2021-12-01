#include "Timer.h"

namespace Timer
{

	Timer::Timer()
	{
		mStart = std::chrono::high_resolution_clock::now();
	}
	void Timer::Start()
	{
		mStart = std::chrono::high_resolution_clock::now();
	}
	float Timer::Stop()
	{
		mEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = mEnd - mStart;
		return duration.count();
	}

	
	LifeTimeTimer::LifeTimeTimer(std::function<void(float time)> onLifetimeEndLisetener)
	{
		this->onLifetimeEndLisetener = onLifetimeEndLisetener;
		mStart = std::chrono::high_resolution_clock::now();
	}
	LifeTimeTimer::~LifeTimeTimer()
	{
		mEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = mEnd - mStart;
		lastTime = duration.count();
		onLifetimeEndLisetener(lastTime);
	}
}