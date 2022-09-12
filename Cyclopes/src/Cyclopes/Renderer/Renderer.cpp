#include "Cycpch.h"
#include "Renderer.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {

	Renderer::Renderer()
	{
		m_GfxContext = GraphicsContext::Create();
	}

	void Renderer::OnInit()
	{
		m_GfxContext->OnInit();
	}

	void Renderer::SetTargetWindow(const std::string& nameId)
	{
		m_GfxContext->MakeCurrent(nameId);
	}

	void Renderer::SwapBuffers(const std::string& nameId)
	{
		m_GfxContext->SwapBuffers(nameId);
	}

	void Renderer::PushWindow(Window* window)
	{
		m_GfxContext->PushWindow(window);
	}

}