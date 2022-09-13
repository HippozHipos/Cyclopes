#pragma once

#include "Cyclopes/Core/Base.h"

namespace cyc {
	
	class Window;
	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

	public:
		static Cyc_Scoped<GraphicsContext> Create();

	public:
		virtual void OnInit() = 0;
		virtual void OnDestory() = 0;

		virtual void MakeCurrent(const Cyc_String& nameId) = 0;
		virtual void SwapBuffers(const Cyc_String& nameId) = 0;
		virtual void PushWindow(Window* window) = 0;
		virtual Window* GetTargetWindow() const = 0;
	};

}
