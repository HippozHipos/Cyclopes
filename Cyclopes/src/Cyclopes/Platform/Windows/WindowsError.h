#pragma once

#include "Cyclopes/Core/Base.h"

namespace cyc {

	CYC_STRING TranslateWin32ErrorCode(HRESULT hr);
}

#ifdef CYC_DEBUG

#define CYC_WIN32_ERRORMSG(cond, win, errorCode, msg)					\
	{																	\
		if (!(cond))													\
		{																\
			win->ErrorMessageBox(										\
				CYC_STRINGIFY(Win32 Error Code) L"\n\n" 				\
				msg L"\n\n" +											\
				TranslateWin32ErrorCode(errorCode) + L"\n\n"			\
				CYC_STRINGIFY([FILE] ) __FILE__ L"\n\n"					\
				CYC_STRINGIFY([LINE] ) + CYC_TO_STRING(__LINE__)		\
			);															\
			CYC_DEBUGBREAK();											\
		}																\
	} 

#define CYC_WIN32_LASTERRORMSG(cond, win, msg)							\
	{																	\
		if (!(cond))													\
		{																\
			win->ErrorMessageBox(										\
				CYC_STRINGIFY(Win32 Last Error) L"\n\n"					\
				msg L"\n\n" +											\
				TranslateWin32ErrorCode(GetLastError()) + L"\n\n"		\
				CYC_STRINGIFY([FILE] ) __FILE__ L"\n\n"					\
				CYC_STRINGIFY([LINE] ) + CYC_TO_STRING(__LINE__)		\
			);															\
			CYC_DEBUGBREAK();											\
		}																\
	} 

#else //CYC_DEBUG
	#define CYC_WIN32_ERRORMSG(cond, win, errorCode, msg)	
	#define CYC_WIN32_LASTERRORMSG(cond, win, msg)		
#endif