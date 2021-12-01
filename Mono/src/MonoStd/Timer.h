#pragma once
#include <chrono>
#include <functional>
namespace Timer
{
	class Timer
	{
		std::chrono::steady_clock::time_point mStart;
		std::chrono::steady_clock::time_point mEnd;
	public:
		Timer();
		void Start();
		/**
		* @returns Time from Start in seconds
		*/
		float Stop();
	};
	class LifeTimeTimer
	{
		std::chrono::steady_clock::time_point mStart;
		std::chrono::steady_clock::time_point mEnd;
	public:
		float lastTime;
		std::function<void(float time)> onLifetimeEndLisetener;
		LifeTimeTimer(std::function<void(float time)> onLifetimeEndLisetener);
		~LifeTimeTimer();
	};
}