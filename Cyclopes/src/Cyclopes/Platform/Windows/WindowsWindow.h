#pragma once

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include "Cyclopes/Core/Base.h"

#include "Cyclopes/Core/Window.h"

#include "Cyclopes/Event/Mouse.h"
#include "Cyclopes/Event/Keyboard.h"
#include "Cyclopes/Event/WindowEvent.h"

//TODO: Add support for window resizing

//TODO: Make window focus when any part of a window is click

namespace cyc {

	class WindowsWindow;
	class Win32NativeWindow
	{
	public:
		Win32NativeWindow(LayerStack& layers);
		~Win32NativeWindow();

	public:
		static int GetWindowCount();
		HWND GetHandle();
		void Init(const WindowProperties& props);
		void Destroy();

	public:
		static LRESULT WINAPI HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		void ErrorMessageBox(Cyc_WString error);

	public:
		const Mouse& GetMouse() const;
		const Keyboard& GetKeyboard() const;

	public:
		//client side event interface
		bool HasEvent() const;
		WindowEvent ReadEvent() const;

	public:
		int rawx = 0;
		int rawy = 0;
		int width = 0;
		int height = 0;

	private:
		void TrimBuffer();

	private:
		//win32 side event interface
		void OnWindowResize();
		void OnWindowFocus();
		void OnWindowMove();
		void OnWindowClose();

	private:
		static constexpr std::uint32_t s_MaxBufferSize = 32u;
		mutable Cyc_Queue<WindowEvent> m_EventBuffer;

	private:
		LayerStack& layers;
		static int s_WindowCount;
		Cyc_WString m_ClassName = L"Cyclopes Window";
		static bool s_HInstanceIsSet;
		static HINSTANCE s_HInstance; 
		HWND m_HWnd = nullptr;
		WNDCLASSEX m_WndClass = { 0 };

	private:
		Mouse m_Mouse;
		Keyboard m_Keyboard;

	};

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		~WindowsWindow();

	public:
		void SetTitle(const std::string& title) override;
		void _Destroy() override;
		bool HasEvent() const override;
		WindowEvent ReadEvent() const override;
		WindowEvent ReadEventNoPop() const;
		bool IsFocused() const override;
		void Focus() override;
		WindowProperties GetProperty() const override;

		const Mouse& GetMouse() const override;
		const Keyboard& GetKeyboard() const override;

		LayerStack& GetLayerStack() override;

		void* GetNativeWindow() override;
		void _UpdateProperty() override;

		void HideCursor(bool hide) override;
		void LockCursor(bool lock) override;
		bool CursorIsLocked() const override;
		bool CursorIsHidden() const override;

	public:
		int GetWindowCount() override;	

	private:
		void Init();

	private:
		WindowProperties m_Properties;
		Cyc_Scoped<Win32NativeWindow> m_Window;
		LayerStack m_Layers;

	private:
		bool m_CursorLocked = false;
		bool m_CursorHidden = false;
	};
}


