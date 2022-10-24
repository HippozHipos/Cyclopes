#pragma once

#include "Cyclopes/Core/Base.h"
#include "Cyclopes/Core/Log.h"

namespace cyc {

	Cyc_WString TranslateWin32ErrorCodeW(HRESULT hr);
	Cyc_String TranslateWin32ErrorCodeA(HRESULT hr);
}

#ifdef CYC_DEBUG

#define CYC_WIN32_ERROR_MSGBOX(cond, win, errorCode, msg)				\
	{																	\
		if (!(cond))													\
		{																\
			win->ErrorMessageBox(										\
				CYC_STRINGIFY(Win32 Error Code) L"\n\n" 				\
				msg L"\n\n" +											\
				cyc::TranslateWin32ErrorCodeW(errorCode) + L"\n\n"		\
				CYC_STRINGIFY([FILE] ) __FILE__ L"\n\n"					\
				CYC_STRINGIFY([LINE] ) + std::to_wstring(__LINE__)		\
			);															\
			CYC_DEBUGBREAK();											\
		}																\
	} 



#define CYC_WIN32_LASTERROR_MSGBOX(cond, win, msg)						\
	{																	\
		if (!(cond))													\
		{																\
			win->ErrorMessageBox(										\
				CYC_STRINGIFY(Win32 Last Error) L"\n\n"					\
				msg L"\n\n" +											\
				cyc::TranslateWin32ErrorCodeW(GetLastError()) + L"\n\n"	\
				CYC_STRINGIFY([FILE] ) __FILE__ L"\n\n"					\
				CYC_STRINGIFY([LINE] ) + std::to_wstring(__LINE__)		\
			);															\
			CYC_DEBUGBREAK();											\
		}																\
	} 

#define CYC_WIN32_LASTERROR(cond, msg)									\
	{																	\
		if (!(cond))													\
		{																\
			CYC_CORE_ERROR(												\
				CYC_STRINGIFY(Win32 Last Error) "\n\n"					\
				msg "\n\n" +											\
				cyc::TranslateWin32ErrorCodeA(GetLastError()) + "\n\n"  \
				CYC_STRINGIFY([FILE] ) __FILE__ "\n\n"					\
				CYC_STRINGIFY([LINE] ) + std::to_string(__LINE__)		\
			);															\
			CYC_DEBUGBREAK();											\
		}																\
	} 


#define CYC_WIN32_LASTERROR_NOBREAK(cond, msg)									\
	{																			\
		if (!(cond))															\
		{																		\
			CYC_CORE_ERROR(														\
				CYC_STRINGIFY(Win32 Last Error) "\n\n"							\
				msg "\n\n" +													\
				cyc::TranslateWin32ErrorCodeA(GetLastError()) + "\n\n"			\
				CYC_STRINGIFY([FILE] ) __FILE__ "\n\n"							\
				CYC_STRINGIFY([LINE] ) + std::to_string(__LINE__)				\
			);																	\
		}																		\
	} 

#else //CYC_DEBUG
	#define CYC_WIN32_ERRORMSG(cond, win, errorCode, msg)	
	#define CYC_WIN32_LASTERROR_MSGBOX(cond, win, msg)		
	#define CYC_WIN32_LASTERROR(cond, msg)		
	#define CYC_WIN32_LASTERROR_NOBREAK(cond, msg)
#endif