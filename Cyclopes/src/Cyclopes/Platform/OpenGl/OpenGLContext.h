#pragma once

#include "Cyclopes/Renderer/GraphicsContext.h"

#include "Cyclopes/Core/Window.h"

namespace cyc {

	class OpenGLContext : public GraphicsContext
	{
	private:
		//gl render context and window info
		struct GLRCWinInfo
		{
			HGLRC glRenderContext;
			Window* window;
		};

	public:
		OpenGLContext();

	public:
		void OnInit() override;
		void MakeCurrent(const std::string& nameId) override;
		void SwapBuffers(const std::string& nameId) override;

		void PushWindow(Window* window) override;

	private:
		PIXELFORMATDESCRIPTOR m_Pfd;
		std::unordered_map<std::string, GLRCWinInfo> m_WinNameIDGLRCWinInfoMap;
		bool m_FirstWindow = true;
	};

}
