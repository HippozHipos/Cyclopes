#pragma once

#include "Base.h"
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#pragma warning(pop)

namespace cyc {

	class Log
	{
	public:
		static void Init();
		static Cyc_Ref<spdlog::logger>& GetClientLogger();
		static Cyc_Ref<spdlog::logger>& GetCoreLogger();
		
	private:
		static Cyc_Ref<spdlog::logger> s_CoreLogger;
		static Cyc_Ref<spdlog::logger> s_ClientLogger;
	};
}

#if defined(CYC_DEBUG) || defined(CYC_RELEASE) 
//core logging macros
#define CYC_CORE_ERROR(...)    ::cyc::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CYC_CORE_WARN(...)     ::cyc::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CYC_CORE_CRITICAL(...) ::cyc::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CYC_CORE_INFO(...)     ::cyc::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CYC_CORE_TRACE(...)    ::cyc::Log::GetCoreLogger()->trace(__VA_ARGS__)

//client logging macros
#define CYC_ERROR(...)    ::cyc::Log::GetClientLogger()->error(__VA_ARGS__)
#define CYC_WARN(...)     ::cyc::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CYC_CRITICAL(...) ::cyc::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CYC_INFO(...)     ::cyc::Log::GetClientLogger()->info(__VA_ARGS__)
#define CYC_TRACE(...)    ::cyc::Log::GetClientLogger()->trace(__VA_ARGS__)
#else
//core logging macros
#define CYC_CORE_ERROR(...)    
#define CYC_CORE_WARN(...)     
#define CYC_CORE_CRITICAL(...) 
#define CYC_CORE_INFO(...)     
#define CYC_CORE_TRACE(...)    

//client logging macros
#define CYC_ERROR(...)    
#define CYC_WARN(...)     
#define CYC_CRITICAL(...) 
#define CYC_INFO(...)     
#define CYC_TRACE(...)    

#endif
