#pragma once

#include "Cyclopes/Renderer/GraphicsContext.h"

#include "Cyclopes/Core/Window.h"

#include "wglext.h"

namespace cyc {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext() = default;
		~OpenGLContext() = default;

	public:
		void OnInit(Window* window) override;
		void SwapBuffers() override;
		void OnDestroy() override;
		void MakeCurrent() override;
		void* GetContext() override;
		void SetSwapInterval(int interval) override;
		void SetViewport(float x, float y, float width, float height) override;

	private:
		int* GetAttributeArray() const;

	private:
		PIXELFORMATDESCRIPTOR m_Pfd{};
		HGLRC m_GLRenderContext = nullptr;
		HDC m_Dc = nullptr;
	};

}
