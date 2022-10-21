#pragma once

#include "Timer.h"
#include "Base.h"

#include "Assert.h"

namespace cyc {

	class Time
	{
	public:
		static float GetDeltaTime();
		static int GetFPS();
		static int GetAverageFPS(int nFrames = 100);

	public:
		//you can look but cannot touch
		static void _Reset();
		static void _UpdateElapsedTime() ;

	private:
		static Timer s_Timer;
		static float s_ElapsedTime;
		static Cyc_Deque<float> s_ElapsedTimePerFrame;
	};
}
