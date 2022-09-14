#include "Cycpch.h"
#include "OpenGLContext.h"

#include "Cyclopes/Core/Assert.h"
#include "GLAD/glad.h"

#include "Cyclopes/Core/Log.h"

namespace cyc {

	void OpenGLContext::OnInit(Window* window)
	{
		m_Pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		m_Dc = ::GetDC((HWND)window->GetNativeWindow());
		m_GLRenderContext = wglCreateContext(m_Dc);

		int pixelFormal = ChoosePixelFormat(m_Dc, &m_Pfd);
		SetPixelFormat(m_Dc, pixelFormal, &m_Pfd);
		m_GLRenderContext = wglCreateContext(m_Dc);

		wglMakeCurrent(m_Dc, m_GLRenderContext);

		if (!gladLoadGL())
		{
			CYC_CORE_ASSERT(false, "Glad loader failed");
		}

	}

	void OpenGLContext::SwapBuffers()
	{		
		::SwapBuffers(m_Dc);
	}

	void OpenGLContext::OnDestory()
	{
		wglDeleteContext(m_GLRenderContext);
	}

	void OpenGLContext::MakeCurrent()
	{
		wglMakeCurrent(m_Dc, m_GLRenderContext);
	}

	void* OpenGLContext::GetContext()
	{
		return (void*)m_GLRenderContext;
	}
}