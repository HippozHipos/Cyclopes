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
		void OnInit();
		void SetTargetWindow(const Cyc_String& nameId);
		void SwapBuffers(const Cyc_String& nameId);
		Window* GetTargetWindow() const;

		void PushWindow(Window* window);

		void OnDestory();

	private:
		Cyc_Scoped<GraphicsContext> m_GfxContext = nullptr;
	};

}

