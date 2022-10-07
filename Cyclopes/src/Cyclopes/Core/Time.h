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
		static void _Reset();
		static void _UpdateElapsedTime() ;

	private:
		static Timer m_Timer;
		static float m_ElapsedTime;
		static Cyc_Deque<float> m_ElapsedTimePerFrame;
	};
}
