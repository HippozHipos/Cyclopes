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
		void SetSwapInterval(int interval);
		void OnDestroy();
		void MakeCurrent();

		void* GetRenderContext();
		void SetViewport(float x, float y, float width, float height);


	private:
		Cyc_Scoped<GraphicsContext> m_GfxContext = nullptr;
	};

}

