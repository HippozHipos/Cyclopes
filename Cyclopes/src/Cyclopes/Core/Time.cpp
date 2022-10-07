#include "Cycpch.h"
#include "Time.h"

namespace cyc {

    Timer Time::m_Timer;
    float Time::m_ElapsedTime = 0;
    Cyc_Deque<float> Time::m_ElapsedTimePerFrame;

	float Time::GetDeltaTime()
	{
		return m_ElapsedTime;
	}

	int Time::GetFPS()
	{
		return (int)(1.0f / m_ElapsedTime);
	}

    int Time::GetAverageFPS(int nFrames)
    {
        CYC_CORE_ASSERT(nFrames > 1,
            "[Application::GetAverageFPS] This function provides an average FPS between "
            "the given number of frames, so the argument must be greater than 1. Maybe use GetFPS(void) instead?");

        if (m_ElapsedTimePerFrame.size() < nFrames)
        {
            m_ElapsedTimePerFrame.push_back(m_ElapsedTime);
        }
        else
        {
            m_ElapsedTimePerFrame.push_back(m_ElapsedTime);
            m_ElapsedTimePerFrame.pop_front();
        }

        float totalElapsedTime = 0;
        for (float elapsedTime : m_ElapsedTimePerFrame)
        {
            totalElapsedTime += elapsedTime;
        }

        return (int)(m_ElapsedTimePerFrame.size() / totalElapsedTime);
    }

	void Time::_Reset()
	{
		m_Timer.Reset();
	}

	void Time::_UpdateElapsedTime()
	{
		float dt = (float)m_Timer.Count<std::chrono::microseconds>();
		m_ElapsedTime = dt * 0.001f * 0.001f;    //convert to seconds
	}



}