#include "Cycpch.h"
#include "Time.h"

namespace cyc {

    Timer Time::s_Timer;
    float Time::s_ElapsedTime = 0;
    Cyc_Deque<float> Time::s_ElapsedTimePerFrame;

	float Time::GetDeltaTime()
	{
		return s_ElapsedTime;
	}

	int Time::GetFPS()
	{
		return (int)(1.0f / s_ElapsedTime);
	}

    int Time::GetAverageFPS(int nFrames)
    {
        CYC_CORE_ASSERT(nFrames > 1,
            "[Application::GetAverageFPS] This function provides an average FPS between "
            "the given number of frames, so the argument must be greater than 1. Maybe use GetFPS(void) instead?");

        if (s_ElapsedTimePerFrame.size() < nFrames)
        {
            s_ElapsedTimePerFrame.push_back(s_ElapsedTime);
        }
        else
        {
            s_ElapsedTimePerFrame.push_back(s_ElapsedTime);
            s_ElapsedTimePerFrame.pop_front();
        }

        float totalElapsedTime = 0;
        for (float elapsedTime : s_ElapsedTimePerFrame)
        {
            totalElapsedTime += elapsedTime;
        }

        return (int)(s_ElapsedTimePerFrame.size() / totalElapsedTime);
    }

	void Time::_Reset()
	{
		s_Timer.Reset();
	}

	void Time::_UpdateElapsedTime()
	{
		float dt = (float)s_Timer.Count<std::chrono::microseconds>();
		s_ElapsedTime = dt * 0.001f * 0.001f;    //convert to seconds
	}



}