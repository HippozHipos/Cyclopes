#pragma once

#include "Cyclopes/Core/Window.h"

namespace cyc {

	class ImGuiContext
	{
	public:
		void OnInit();
		void SetRenderWindow(Window* window, HGLRC glRenderContext);
		void OnDestroy();

		void OnBeginRender();
		bool OnEndRender();

	private:
		Window* m_RenderWindow = nullptr;
	};

}
