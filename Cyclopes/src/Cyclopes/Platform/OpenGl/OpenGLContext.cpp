#include "Cycpch.h"
#include "OpenGLContext.h"

#include "Cyclopes/Core/Assert.h"
#include "GLAD/glad.h"

#include "Cyclopes/Core/Log.h"

namespace cyc {

	void OpenGLContext::OnInit()
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
	}

	void OpenGLContext::MakeCurrent(const std::string& nameId)
	{
		auto it = m_WinNameIDGLRCWinInfoMap.find(nameId);

		if (it == m_WinNameIDGLRCWinInfoMap.end())
		{
			CYC_CORE_ASSERT(false,
				"[OpenGLContext::MakeCurrent] Window with name = \"" + nameId + 
				"\" has not been registered.");
		}

		HDC dc = ::GetDC((HWND)it->second.window->GetNativeWindow());

		m_targetWindow = it->second.window;
		wglMakeCurrent(dc, it->second.glRenderContext);
	}

	void OpenGLContext::SwapBuffers(const std::string& nameId)
	{
		auto it = m_WinNameIDGLRCWinInfoMap.find(nameId);

		if (it == m_WinNameIDGLRCWinInfoMap.end())
		{
			CYC_CORE_ASSERT(false,
				"[OpenGLContext::SwapBuffers] Window with name = \"" + nameId + 
				"\" has not been registered.");
		}

		HDC dc = ::GetDC((HWND)it->second.window->GetNativeWindow());
		::SwapBuffers(dc);
	}

	void OpenGLContext::PushWindow(Window* window)
	{
		HDC dc = ::GetDC((HWND)window->GetNativeWindow());
		int pixelFormal = ChoosePixelFormat(dc, &m_Pfd);
		SetPixelFormat(dc, pixelFormal, &m_Pfd);

		m_WinNameIDGLRCWinInfoMap.insert(
			std::pair<std::string, GLRCWinInfo>(
				window->GetNameId(), 
				{ wglCreateContext(dc), window }
		));

		if (m_FirstWindow)
		{
			m_FirstWindow = false;
			MakeCurrent(window->GetNameId());
			if (!gladLoadGL())
			{
				CYC_CORE_ASSERT(false, "Function gladLoadGL failed");
			}
		}
	}

	Window* OpenGLContext::GetTargetWindow() const
	{
		return m_targetWindow;
	}

	void OpenGLContext::OnDestory()
	{
	}
}