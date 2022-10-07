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
		void Init(Window* window) override;
		void SwapBuffers() override;
		void Destroy() override;
		void MakeCurrent() override;
		void* GetContext() override;
		void SetSwapInterval(int interval) override;
		void SetViewport(float x, float y, float width, float height) override;

	private:
		void GetAttributeArray(int attributeArr[9]) const;

	private:
		PIXELFORMATDESCRIPTOR m_Pfd{};
		HGLRC m_GLRenderContext = nullptr;
		HDC m_Dc = nullptr;
		HWND m_HWnd;
	};

}
