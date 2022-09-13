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
		static RenderCommands command;
		void SwapBuffers(const Cyc_String& nameId);

		void PushWindow(Window* window);

	private:
		Window* m_TargetWindow = nullptr;
		Cyc_Scoped<GraphicsContext> m_GfxContext = nullptr;
		Cyc_Vector<Window*> m_Windows;
	};

}

