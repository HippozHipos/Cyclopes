#include "Cycpch.h"

#include "Window.h"

#ifdef CYC_PLATFORM_WINDOWS
	#include "Cyclopes/Platform/Windows/WindowsWindow.h"
#endif

namespace cyc {

	Cyc_Scoped<Window> Window::Create(const Cyc_String& nameId, const WindowProperties& props)
	{
#ifdef CYC_PLATFORM_WINDOWS
		return Cyc_MakeScoped<WindowsWindow>(nameId, props);
#endif
	}

	void Window::SetIsRegistered()
	{
		m_IsResgistered = true;
	}

	bool Window::IsRegisreted() const
	{
		return m_IsResgistered;
	}

	bool HasWindow()
	{
#ifdef CYC_PLATFORM_WINDOWS
		MSG msg;
		while (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE))
		{
			//msg.wParam contains quit message. Might want to return that
			if (WindowsWindow::GetWindowCount() == 0)
				return false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
#endif
	}
}
