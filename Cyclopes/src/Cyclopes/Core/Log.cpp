#include <Cycpch.h>
#include "Log.h"

namespace cyc {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
#if (defined(CYC_DEBUG) || defined(CYC_RELEASE)) && defined(CYC_PLATFORM_WINDOWS)
		//https ://justcheckingonall.wordpress.com/2008/08/29/console-window-win32-app/
		AllocConsole();

		HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
		int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
		FILE* hf_out = _fdopen(hCrt, "w");
		setvbuf(hf_out, NULL, _IONBF, 1);
		*stdout = *hf_out;

		HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
		hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
		FILE* hf_in = _fdopen(hCrt, "r");
		setvbuf(hf_in, NULL, _IONBF, 128);
		*stdin = *hf_in;
#endif

		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("CORE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("CLIENT");
		s_ClientLogger->set_level(spdlog::level::trace);

		CYC_CORE_INFO("Logger Initialized");
	}

	Ref<spdlog::logger>& Log::GetClientLogger()
	{
		return s_ClientLogger;
	}

	Ref<spdlog::logger>& Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}
}