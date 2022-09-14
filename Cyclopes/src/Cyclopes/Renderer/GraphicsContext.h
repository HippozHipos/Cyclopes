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
		virtual void OnInit(Window* window) = 0;
		virtual void OnDestory() = 0;
		virtual void SwapBuffers() = 0;
		virtual void MakeCurrent() = 0;
		virtual void* GetContext() = 0;
	};

}
