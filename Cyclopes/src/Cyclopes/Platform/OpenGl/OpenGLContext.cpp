#include "Cycpch.h"
#include "OpenGLContext.h"

#include "Cyclopes/Core/Assert.h"
#include "GLAD/glad.h"

#include "OpenGLError.h"

#include "Cyclopes/Platform/Windows/WindowsError.h"
#include "wglext.h"

namespace cyc {

	void OpenGLContext::OnInit(Window* window)
	{
		m_HWnd = (HWND)window->GetNativeWindow();

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
		CYC_CORE_ASSERT(m_Dc,
			"GetDC() failed. Could not retrieve Device Context from window handle");

		int pixelFormal = ChoosePixelFormat(m_Dc, &m_Pfd);
		CYC_WIN32_LASTERROR(pixelFormal,
			"ChoosePixelFormat() failed. Could not find a suitable pixel format");

		BOOL res = SetPixelFormat(m_Dc, pixelFormal, &m_Pfd);
		CYC_WIN32_LASTERROR(res, 
			"SetPixelFormat() failed. Could not set the specified pixel format");

		HGLRC tempContext = wglCreateContext(m_Dc);
		CYC_WIN32_LASTERROR(tempContext, 
			"wglCreateContext() failed. Could not created the dummy context");

		wglMakeCurrent(m_Dc, tempContext);
		CYC_WIN32_LASTERROR(tempContext, 
			"wglMakeCurrent() failed. Could not set the dummy context to current context");

		int success = gladLoadGL();
		CYC_CORE_ASSERT(success, 
			"gladLoadGL() failed. Glad could not load opengl function pointers");

		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB
			= (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		CYC_WIN32_LASTERROR(wglCreateContextAttribsARB,
			"GetAnyGLFuncAddress() failed. Failed to load wglCreateContextAttribsARB function pointer");

		int arrtibuteArray[9];
		GetAttributeArray(arrtibuteArray);
		m_GLRenderContext = wglCreateContextAttribsARB(m_Dc, 0, arrtibuteArray);
		CYC_WIN32_LASTERROR(wglCreateContextAttribsARB,
			"wglCreateContextAttribsARB() failed. Could not create gl render context from given atttributes");

		res = wglDeleteContext(tempContext);
		CYC_WIN32_LASTERROR(res, 
			"wglDeleteContext() failed. Could not delete the dummy context");

		MakeCurrent();
		SetSwapInterval(1);

#if defined(CYC_DEBUG) || defined(CYC_RELEASE)
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLErrorMessageCallback, 0);
#endif
	}

	void OpenGLContext::SwapBuffers()
	{		
		HDC dc = ::GetDC(m_HWnd);

		if (!dc)
		{
			CYC_CORE_WARN("[OpenGLContext::SwapBuffers] Couldn't retrieve Device Context from window handle. Is window handle valid?");
			return;
		}

		BOOL res = ::SwapBuffers(dc);
		CYC_WIN32_LASTERROR(res,
			"SwapBuffers() failed. Could not swap buffers with the given Device Context");
	}

	void OpenGLContext::OnDestroy()
	{
		BOOL res = wglDeleteContext(m_GLRenderContext);
		CYC_WIN32_LASTERROR(res,
			"wglDeleteContext() failed. Could not delete gl render context");
	}

	void OpenGLContext::MakeCurrent()
	{
		BOOL res = wglMakeCurrent(m_Dc, m_GLRenderContext);
		CYC_WIN32_LASTERROR(res,
			"wglMakeCurrent() failed. Could not set gl render context to current");
	}

	void* OpenGLContext::GetContext()
	{
		return (void*)m_GLRenderContext;
	}

	void OpenGLContext::SetSwapInterval(int interval)
	{
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
			(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

		CYC_WIN32_LASTERROR(wglSwapIntervalEXT,
			"wglSwapIntervalEXT() failed. Could not load wglSwapIntervalEXT function pointer");
		
		BOOL res = wglSwapIntervalEXT(interval);
		CYC_WIN32_LASTERROR(res,
			"wglSwapIntervalEXT() failed. Swap interval could not be set");
	}

	void OpenGLContext::SetViewport(float x, float y, float width, float height)
	{
		glViewport((int)x, (int)y, (int)width, (int)height);
	}

	void OpenGLContext::GetAttributeArray(int attributeArr[9]) const
	{
		int flags = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
#if CYC_DEBUG
		flags |= WGL_CONTEXT_DEBUG_BIT_ARB;
#endif
		attributeArr[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
		attributeArr[1] = 3;
		attributeArr[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
		attributeArr[3] = 3;
		attributeArr[4] = WGL_CONTEXT_FLAGS_ARB;
		attributeArr[5] = flags;
		attributeArr[6] = WGL_CONTEXT_PROFILE_MASK_ARB;
		attributeArr[7] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
		attributeArr[8] = 0;
	}
}