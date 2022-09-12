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
		void SetTargetWindow(const std::string& nameId);
		static RenderCommands command;
		void SwapBuffers(const std::string& nameId);

		void PushWindow(Window* window);

	private:
		Window* m_TargetWindow = nullptr;
		Scoped<GraphicsContext> m_GfxContext = nullptr;
		std::vector<Window*> m_Windows;
	};

}

