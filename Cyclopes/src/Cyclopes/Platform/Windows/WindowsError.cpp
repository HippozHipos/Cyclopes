#include "Cycpch.h"
#include "WindowsError.h"

namespace cyc {

	CYC_STRING TranslateWin32ErrorCode(HRESULT hr)
	{
		wchar_t* msgBuffer = nullptr;
		DWORD nMsgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPWSTR>(&msgBuffer), 0, nullptr
		);

		if (nMsgLen == 0)
		{
			return L"Undefined Error Code";
		}

		CYC_STRING error = msgBuffer;
		LocalFree(msgBuffer);
		return error;
	}

}
