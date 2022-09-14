#pragma once

#include "Cyclopes/Renderer/GraphicsContext.h"

#include "Cyclopes/Core/Window.h"

namespace cyc {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext() = default;
		~OpenGLContext() = default;

	public:
		void OnInit(Window* window) override;
		void SwapBuffers() override;
		void OnDestory() override;
		void MakeCurrent() override;
		void* GetContext() override;

	private:
		PIXELFORMATDESCRIPTOR m_Pfd{};
		HGLRC m_GLRenderContext = nullptr;
		HDC m_Dc = nullptr;
	};

}
