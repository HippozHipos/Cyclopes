#pragma once

#ifdef CYC_PLATFORM_WINDOWS
	//FunctionNameW version of functions in win32 api are used thoughout
	#ifndef UNICODE
		#define UNICODE
	#endif

	#define CYC_STRING std::wstring	

	#define CYC_TO_STRING std::to_wstring

#else
	#error Cyclopes currently only supports windows
#endif

#define BIT(n) 1 << n


#include <memory>

namespace cyc {

	template<class Type> using Ref = std::shared_ptr<Type>;
	template<class Type> using Scoped = std::unique_ptr<Type>;

	//template<class Type> using MakeRef = std::make_shared<Type>;
	//template<class Type> using MakeScoped = std::make_unique<Type>;
}