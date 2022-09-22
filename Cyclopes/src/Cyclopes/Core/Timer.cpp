#include "Cycpch.h"
#include "Timer.h"

namespace cyc {

	void Timer::Reset() noexcept
	{
		start = std::chrono::high_resolution_clock::now();
	}
	
}