#include "Cycpch.h"

#include "WindowsWindow.h"
#include "WindowsError.h"

#include "Cyclopes/Core/Assert.h"

#include "Cyclopes/ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace cyc {

	namespace {

		bool N_RegisterMouseRawInput()
		{
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 0x01;          // HID_USAGE_PAGE_GENERIC
			rid.usUsage = 0x02;              // HID_USAGE_GENERIC_MOUSE
			rid.dwFlags = 0;
			rid.hwndTarget = nullptr;

			if (RegisterRawInputDevices(&rid, 1, sizeof(rid)) == FALSE)
			{
				CYC_WIN32_LASTERROR_NOBREAK(false, "[N_RegisterMouseRawInput] RegisterRawInputDevices failed");
				return false;
			}

			return true;
		}

		RAWINPUT* N_GetRawInputData(LPARAM lParam)
		{
			UINT dwSize = 0;
			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == NULL) return nullptr;

			if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
				CYC_CORE_WARN("[N_GetRawInputData] GetRawInputData did not return correct size\n");

			return (RAWINPUT*)lpb;
		}

	}


	HINSTANCE Win32NativeWindow::s_HInstance = nullptr;
	int Win32NativeWindow::s_WindowCount = 0;
	bool Win32NativeWindow::s_HInstanceIsSet = false;

	void Win32NativeWindow::Init(const WindowProperties& props)
	{
		rawx = props.rawx;
		rawy = props.rawy;
		width = props.width;
		height = props.height;

		m_WndClass.cbSize = sizeof(m_WndClass);
		m_WndClass.style = CS_OWNDC;
		m_WndClass.lpfnWndProc = HandleMessageSetup;
		m_WndClass.cbClsExtra = 0;
		m_WndClass.cbWndExtra = 0;
		m_WndClass.hInstance = s_HInstance;
		m_WndClass.hIcon = nullptr;
		m_WndClass.hCursor = nullptr;
		m_WndClass.hbrBackground = nullptr;
		m_WndClass.lpszMenuName = nullptr;
		m_WndClass.lpszClassName = m_ClassName.c_str();
		m_WndClass.hIconSm = nullptr;

		ATOM res = ::RegisterClassEx(&m_WndClass);
		CYC_WIN32_LASTERROR_MSGBOX(res, this, L"RegisterClassEx function failed."
		                                    "Could not register Win32 window");

		//convert string to wstring
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		Cyc_WString wTitle = converter.from_bytes(props.title);

		RECT wr;
		wr.left = 0; wr.top = 0;
		wr.right = width; wr.bottom = height;

		AdjustWindowRectEx(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU, 0, 0);

		m_HWnd = ::CreateWindowEx(
			0,
			m_ClassName.c_str(),
			wTitle.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
			props.rawx, props.rawy, wr.right - wr.left, wr.bottom - wr.top,
			nullptr,
			nullptr,
			s_HInstance,
			this
		);

		CYC_WIN32_LASTERROR_MSGBOX(m_HWnd, this, L"CreateWindowEx function failed. "
												"Window Handle is NULL");

		N_RegisterMouseRawInput();
		
		ShowWindow(m_HWnd, SW_SHOWDEFAULT);
	}

	Win32NativeWindow::Win32NativeWindow(LayerStack& layers) :
		layers(layers)
	{
		s_HInstance = GetModuleHandle(NULL);
		s_WindowCount++;
		m_ClassName += std::to_wstring(s_WindowCount);
	}

	Win32NativeWindow::~Win32NativeWindow() 
	{
	}

	int Win32NativeWindow::GetWindowCount()
	{
		return s_WindowCount;
	}

	LRESULT WINAPI Win32NativeWindow::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			//extract the windows window class
			CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
			Win32NativeWindow* const win32Win = static_cast<Win32NativeWindow*>(create->lpCreateParams);

			//store windows window on the win32 api side
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(win32Win));

			//set window proc to the actual message handler.
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32NativeWindow::HandleMessageThunk));

			return win32Win->HandleMessage(hWnd, msg, wParam, lParam);
		}
	}

	LRESULT WINAPI Win32NativeWindow::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		auto win = reinterpret_cast<Win32NativeWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return win->HandleMessage(hWnd, msg, wParam, lParam);
	}

	LRESULT Win32NativeWindow::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		{
			return true;
		}

		switch (msg)
		{
			case WM_INPUT:
			{
				RAWINPUT* raw = N_GetRawInputData(lParam);
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					m_Mouse.OnMouseRawInput(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
				delete raw;
				break;
			}

			case WM_CLOSE:
			{
				layers._OnEvent(WindowEvent(EventType::W_CLOSE));
				PostQuitMessage(0);
				OnWindowClose();
				return 0;
			}

			case WM_MOVE:
			{
				layers._OnEvent(WindowEvent(EventType::W_MOVED));
				RECT rect;
				if (GetWindowRect(m_HWnd, &rect))
				{
					rawx = rect.left;
					rawy = rect.top;
				}
				OnWindowMove();
				break;
			}

			case WM_KILLFOCUS:
			{
				layers._OnEvent(WindowEvent(EventType::W_FOCUS_KILLED));
				m_Keyboard.ClearState();
				break;
			}

			case WM_SETFOCUS:
			{
				layers._OnEvent(WindowEvent(EventType::W_FOCUSED));
				SetFocus(m_HWnd);
				OnWindowFocus();
				break;
			}

			//UPDATE WINDOWS SIZE STORED IN CLASS SO THAT IT IS ACCURATE WHEN MOUSE EVENTS
			case WM_SIZE:
			{
				layers._OnEvent(WindowEvent(EventType::W_RESIZED));
				OnWindowResize();
				//figure out how to handle window resizing.
				RECT rect;
				if (GetClientRect(m_HWnd, &rect))
				{
					width = rect.right - rect.left;
					height = rect.bottom - rect.top;
				}
				break;
			}

			///////////////////////////////////////////////////////
			///////////////    MOUSE EVENTS    ////////////////////
			///////////////////////////////////////////////////////
			case WM_LBUTTONDOWN:
			{
				layers._OnEvent(MouseEvent(EventType::M_LBUTTON_DOWN));
				m_Mouse.OnLButtonDown();
				break;
			}
			case WM_RBUTTONDOWN:
			{
				layers._OnEvent(MouseEvent(EventType::M_RBUTTON_DOWN));
				m_Mouse.OnRButtonDown();
				break;
			}
			case WM_LBUTTONUP:
			{
				layers._OnEvent(MouseEvent(EventType::M_LBUTTON_UP));
				m_Mouse.OnLButtonUp();
				break;
			}
			case WM_RBUTTONUP:
			{
				layers._OnEvent(MouseEvent(EventType::M_RBUTTON_UP));
				m_Mouse.OnLButtonUp();
				break;
			}
			case WM_MOUSEWHEEL:
			{
				//TODO: IMPLEMENT THIS
				layers._OnEvent(MouseEvent(EventType::M_WHEEL_SCROLL_DOWN));
				layers._OnEvent(MouseEvent(EventType::M_WHEEL_SCROLL_UP));
				break;
			}
			case WM_MOUSEMOVE:
			{
				layers._OnEvent(MouseEvent(EventType::M_MOVED));
				POINTS p = MAKEPOINTS(lParam);

				//if the mouse is dragged out of the window while clicking,
				//it still counts as mouse being in the window
				if (p.x > 0 && p.x < width && p.y > 0 && p.y < height)
				{
					m_Mouse.OnMouseMove(p.x, p.y);
					if (!m_Mouse.IsInWindow())
					{
						//pushes window event to event queue
						SetCapture(hWnd);
						layers._OnEvent(MouseEvent(EventType::M_ENTERED_WINDOW));
						m_Mouse.OnMouseEnter();
					}
				}
				else
				{
					if (wParam & (WM_LBUTTONDOWN | WM_RBUTTONDOWN))
					{
						m_Mouse.OnMouseMove(p.x, p.y);
					}
					else
					{
						ReleaseCapture();
						layers._OnEvent(MouseEvent(EventType::M_LEFT_WINDOW));
						m_Mouse.OnMouseLeave();
					}
				}
				
				break;
			}

			//////////////////////////////////////////////////////
			///////////////    KEYBOARD EVENTS    ////////////////
			//////////////////////////////////////////////////////
			case WM_KEYUP: 
			case WM_SYSKEYUP:
			{
				m_Keyboard.OnKeyUp((unsigned char)(wParam));
				layers._OnEvent(KeyEvent(EventType::K_RELEASED));
				break;
			}
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			{
				if (!(lParam & BIT(30)) || m_Keyboard.AutoRepeatIsEnabled())
				{
					m_Keyboard.OnKeyDown((unsigned char)(wParam));
					layers._OnEvent(KeyEvent(EventType::K_RELEASED));
				}
				break;
			}
			case WM_CHAR:
			{
				m_Keyboard.OnChar((unsigned char)(wParam));
			}
		}

		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	void Win32NativeWindow::OnWindowResize()
	{
		m_EventBuffer.push(WindowEvent(EventType::W_RESIZED));
		TrimBuffer();
	}

	void Win32NativeWindow::OnWindowFocus()
	{
		m_EventBuffer.push(WindowEvent(EventType::W_FOCUSED));
		TrimBuffer();
	}

	void Win32NativeWindow::OnWindowMove()
	{
		m_EventBuffer.push(WindowEvent(EventType::W_MOVED));
		TrimBuffer();
	}

	void Win32NativeWindow::OnWindowClose()
	{
		m_EventBuffer.push(WindowEvent(EventType::W_CLOSE));
		TrimBuffer();
	}

	bool Win32NativeWindow::HasEvent() const
	{
		return !m_EventBuffer.empty();
	}

	WindowEvent Win32NativeWindow::ReadEvent() const
	{
		WindowEvent out = m_EventBuffer.front();
		m_EventBuffer.pop();
		return out;
	}

	void Win32NativeWindow::TrimBuffer()
	{
		while (m_EventBuffer.size() > s_MaxBufferSize)
			m_EventBuffer.pop();
	}
	
	HWND Win32NativeWindow::GetHandle()
	{
		return m_HWnd;
	}

	void Win32NativeWindow::Destroy()
	{
		s_WindowCount--;
		DestroyWindow(m_HWnd);
		UnregisterClass(m_ClassName.c_str(), s_HInstance);
	}

	void Win32NativeWindow::ErrorMessageBox(Cyc_WString error)
	{
		MessageBox(m_HWnd, error.c_str(),
			L"Cyclopes Win32 Error", MB_OK | MB_ICONERROR);
	}

	const Mouse& Win32NativeWindow::GetMouse() const
	{
		return m_Mouse;
	}

	const Keyboard& Win32NativeWindow::GetKeyboard() const
	{
		return m_Keyboard;
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props) :
			m_Layers(this), m_Properties(props)
	{
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::_UpdateProperty()
	{
		m_Properties.rawx = m_Window->rawx;
		m_Properties.rawy = m_Window->rawy;
		m_Properties.width = m_Window->width;
		m_Properties.height = m_Window->height;
	}

	void WindowsWindow::HideCursor(bool hide)
	{
		::ShowCursor(!hide);
		m_CursorHidden = hide;
	}

	bool WindowsWindow::CursorIsHidden() const
	{
		return m_CursorHidden;
	}

	void WindowsWindow::LockCursor(bool lock)
	{
		m_CursorLocked = lock;
	}

	bool WindowsWindow::CursorIsLocked() const
	{
		return m_CursorLocked;
	}

	void WindowsWindow::Init()
	{
		m_Window = std::make_unique<Win32NativeWindow>(m_Layers);
		m_Window->Init(m_Properties);
	}

	void WindowsWindow::_Destroy()
	{
		m_Window->Destroy();
	}

	bool WindowsWindow::HasEvent() const
	{
		return m_Window->HasEvent();
	}

	WindowEvent WindowsWindow::ReadEvent() const
	{
		return m_Window->ReadEvent();
	}

	bool WindowsWindow::IsFocused() const
	{
		return GetFocus() == m_Window->GetHandle();
	}

	void WindowsWindow::Focus()
	{
		::SetFocus(m_Window->GetHandle());
	}

	WindowProperties WindowsWindow::GetProperty() const
	{
		return m_Properties;
	}

	int WindowsWindow::GetWindowCount()
	{
		return Win32NativeWindow::GetWindowCount();
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		Cyc_WString wTitle = converter.from_bytes(title);
		SetWindowText(m_Window->GetHandle(), wTitle.c_str());
		m_Properties.title = title;
	}

	const Mouse& WindowsWindow::GetMouse() const
	{
		return m_Window->GetMouse();
	}

	const Keyboard& WindowsWindow::GetKeyboard() const
	{
		return m_Window->GetKeyboard();
	}

	LayerStack& WindowsWindow::GetLayerStack()
	{
		return m_Layers;
	}

	void* WindowsWindow::GetNativeWindow()
	{
		return m_Window->GetHandle();
	}

}