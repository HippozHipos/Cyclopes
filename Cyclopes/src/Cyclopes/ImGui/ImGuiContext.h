#pragma once

#include "Cyclopes/Core/Window.h"
#include <imgui_internal.h>

namespace cyc {

	class ImGuiContext
	{
	public:
		void OnInit();
		void SetRenderWindow(Window* window);
		Window* GetRenderWindow() const;
		void OnDestroy();

		void OnBeginRender();
		void OnEndRender();

	private:
		Window* m_RenderWindow = nullptr;
	};

}
