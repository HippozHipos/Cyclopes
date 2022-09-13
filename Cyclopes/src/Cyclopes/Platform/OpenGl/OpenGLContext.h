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
		OpenGLContext() = default;
		~OpenGLContext() = default;

	public:
		void OnInit() override;
		void MakeCurrent(const std::string& nameId) override;
		void SwapBuffers(const std::string& nameId) override;
		void PushWindow(Window* window) override;
		Window* GetTargetWindow() const override;
		void OnDestory() override;

	private:
		PIXELFORMATDESCRIPTOR m_Pfd{};
		Cyc_UnorderedMap<Cyc_String, GLRCWinInfo> m_WinNameIDGLRCWinInfoMap;
		Window* m_targetWindow = nullptr;
		bool m_FirstWindow = true;
	};

}
