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
		static Scoped<GraphicsContext> Create();

	public:
		virtual void OnInit() = 0;
		virtual void MakeCurrent(const std::string& nameId) = 0;
		virtual void SwapBuffers(const std::string& nameId) = 0;
		virtual void PushWindow(Window* window) = 0;
	};

}
