#pragma once

#include "Log.h"

#define CYC_STRINGIFY(a) #a

#ifdef CYC_PLATFORM_WINDOWS
	#define CYC_DEBUGBREAK __debugbreak
#else
	#error "Cyclopes only supports windows"
#endif

#include <string.h>

#ifdef CYC_PLATFORM_WINDOWS
	#if defined(CYC_DEBUG) || defined(CYC_RELEASE)
		#define CYC_CORE_ASSERT_WIN32MSG(cond, win, error)						\
			{																	\
				if (!(cond))													\
				{																\
					win->ErrorMessageBox(										\
						CYC_STRINGIFY(Cyclopes Core Assertion Failed) L"\n\n"	\
						error L"\n\n"											\
						CYC_STRINGIFY([FILE] ) __FILE__ L"\n\n"					\
						CYC_STRINGIFY([LINE] ) + CYC_TO_STRING(__LINE__)		\
					);															\
					CYC_DEBUGBREAK();											\
				}																\
			} 

		#define CYC_CORE_ASSERT(cond, ...)										\
			{																	\
				if (!(cond))													\
				{																\
					CYC_CORE_ERROR(__VA_ARGS__);								\
					CYC_DEBUGBREAK();											\
				}																\
			} 

		#define CYC_ASSERT(cond, ...)											\
			{																	\
				if (!(cond))													\
				{																\
					CYC_ERROR(__VA_ARGS__);										\
					CYC_DEBUGBREAK();											\
				}																\
			} 
	#else
		#define CYC_CORE_ASSERT_WIN32MSG(cond, win, error)	
		#define CYC_CORE_ASSERT(cond, ...)
		#define CYC_ASSERT(cond, ...)	

	#endif

#endif