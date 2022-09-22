#pragma once
#include <chrono>

namespace cyc {

	class Timer
	{
	public:
		template<class DurationType>
		int64_t Count() const noexcept
		{
			return std::chrono::duration_cast<DurationType>(std::chrono::high_resolution_clock::now() - start).count();
		}

		void Reset() noexcept;

	private:
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	};
}
