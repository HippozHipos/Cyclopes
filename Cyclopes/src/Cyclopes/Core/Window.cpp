#include "Cycpch.h"
#include "Window.h"

#include "Cyclopes/Core/Log.h"

#ifdef CYC_PLATFORM_WINDOWS
	#include "Cyclopes/Platform/Windows/WindowsWindow.h"
#endif

namespace cyc {

	Cyc_Scoped<Window> Window::Create(const WindowProperties& props)
	{
#ifdef CYC_PLATFORM_WINDOWS
		return Cyc_MakeScoped<WindowsWindow>(props);
#endif
	}

	bool RunMessagePump()
	{
#ifdef CYC_PLATFORM_WINDOWS
		MSG msg;
		while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
#endif
	}
}
