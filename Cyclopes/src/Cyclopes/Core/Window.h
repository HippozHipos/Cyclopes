#pragma once

#include "Base.h"

#include "Cyclopes/Event/Mouse.h"
#include "Cyclopes/Event/Keyboard.h"
#include "Cyclopes/Event/WindowEvent.h"

#include "Cyclopes/Core/LayerStack.h"

#include <memory>
#include <bitset>

namespace cyc {

	class WindowProperties
	{
	public:
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		Cyc_String title = "";
	};

	class Window
	{
	public:
		Window() = default;
		virtual ~Window() = default;

	public:
		virtual void SetVSync(bool enable) = 0;
		virtual bool VSyncIsEnabled() const = 0;
		virtual bool IsFocused() const = 0;
		virtual void Focus() = 0;
		virtual const Mouse& GetMouse() const = 0;
		virtual const Keyboard& GetKeyboard() const = 0;
		virtual void Destroy() = 0;
		virtual void SetTitle(const std::string& title) = 0;
		virtual bool HasEvent() const = 0;
		virtual WindowEvent ReadEvent() const = 0;
		virtual LayerStack& GetLayerStack() = 0;
		virtual void UpdateProperty() = 0;
		virtual WindowProperties GetProperty() const = 0;
		virtual int GetWindowCount() = 0;

	public:
		//native window refers to the underlying os-specific window.
		//For windows, it is HWND. 
		//REMEMBER: UPDATE COMMENT AS OTHER PLATFORMS ARE ADDED
		virtual void* GetNativeWindow() = 0; 

	public:
		static Cyc_Scoped<Window> 
		Create(const WindowProperties& props = {100, 100, 600, 500, "Cyclopes Window"});

	protected:
		bool m_VSyncEnabled = false;
	};

	bool RunMessagePump();
}

