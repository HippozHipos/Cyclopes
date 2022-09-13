#pragma once

#ifdef CYC_PLATFORM_WINDOWS
	//FunctionNameW version of functions in win32 api are used thoughout
	#ifndef UNICODE
		#define UNICODE
	#endif
#else
	#error Cyclopes currently only supports windows
#endif

#define BIT(n) 1 << n


#include <memory>
#include <vector>
#include <queue>
#include <unordered_map>
#include <xstring>

namespace cyc {

	template<class Type> using Cyc_Ref = std::shared_ptr<Type>;
	template<class Type> using Cyc_Scoped = std::unique_ptr<Type>;


	template<class Type> using Cyc_Vector = std::vector<Type>;

	template<class Type> using Cyc_Queue = std::queue<Type>;

	template<class First, class Second> using Cyc_UnorderedMap = std::unordered_map<First, Second>;

	using Cyc_String = std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
	using Cyc_WString = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;

	template<class Type, class... Args> 
	Cyc_Ref<Type> Cyc_MakeShared(Args&&... args)
	{
		return Cyc_Ref<Type>(new Type(std::forward<Args>(args)...));
	}

	template<class Type, class... Args>
	Cyc_Scoped<Type> Cyc_MakeScoped(Args&&... args)
	{
		return Cyc_Scoped<Type>(new Type(std::forward<Args>(args)...));
	}
}