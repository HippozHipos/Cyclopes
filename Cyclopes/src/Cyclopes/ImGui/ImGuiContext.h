#pragma once

#include "Cyclopes/Core/Window.h"

namespace cyc {

	class ImGuiContext
	{
	public:
		void OnInit();
		void InitWin32OpenGL(Window* window);
		void OnDestroy();

		void OnBeginRender();
		void OnEndRender();

	private:
		Window* m_RenderWindow = nullptr;
	};

}
