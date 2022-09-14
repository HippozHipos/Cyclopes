#pragma once

#include "GraphicsContext.h"
#include "Cyclopes/Core/Window.h"

#include "RenderCommands.h"

namespace cyc {

	class Renderer
	{
	public:
		Renderer();

	public:
		void OnInit(Window* window);
		void SwapBuffers();
		void OnDestory();
		void MakeCurrent();

		HGLRC GetRenderContext();

	private:
		Cyc_Scoped<GraphicsContext> m_GfxContext = nullptr;
	};

}

