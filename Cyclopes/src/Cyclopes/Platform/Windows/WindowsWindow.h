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

#include <string>

//TODO: Window size currently includes non-clint region as well. Fix that.

//TODO: Add support for window resizing

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
		void ErrorMessageBox(CYC_STRING error);

	public:
		const Mouse& GetMouse() const;
		const Keyboard& GetKeyboard() const;

	public:
		//client side event interface
		bool HasEvent() const;
		WindowEvent ReadEvent() const;

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
		mutable std::queue<WindowEvent> m_EventBuffer;

	private:
		int width = 0;
		int height = 0;

	private:
		LayerStack& layers;
		static int s_WindowCount;
		CYC_STRING m_ClassName = L"Cyclopes Window";
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
		WindowsWindow(const std::string& nameId, const WindowProperties& props);
		~WindowsWindow();

	public:
		void SetVSync(bool enable) override;
		bool VSyncIsEnabled() const override;
		void SetTitle(const std::string& title) override;
		void Destroy() override;
		bool HasEvent() const override;
		WindowEvent ReadEvent() const override;
		bool IsFocused() const override;
		void Focus() override;
		const std::string& GetNameId() const override;

		const Mouse& GetMouse() const override;
		const Keyboard& GetKeyboard() const override;

		LayerStack& GetLayerStack() override;

		void* GetNativeWindow() override;

	public:
		static int GetWindowCount();	

	private:
		void Init();

	private:
		std::string m_NameId = "";
		WindowProperties m_Properties;
		Scoped<Win32NativeWindow> m_Window;
		LayerStack m_Layers;
	};
}


