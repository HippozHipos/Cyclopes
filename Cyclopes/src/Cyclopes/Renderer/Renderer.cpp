#include "Cycpch.h"
#include "Renderer.h"

#include "Cyclopes/Core/Assert.h"

namespace cyc {

	Renderer::Renderer()
	{
		m_GfxContext = GraphicsContext::Create();
	}

	void Renderer::OnInit(Window* window)
	{
		m_GfxContext->OnInit(window);
	}

	void Renderer::SwapBuffers()
	{
		m_GfxContext->SwapBuffers();
	}

	void Renderer::OnDestory()
	{
		m_GfxContext->OnDestory();
	}

	void Renderer::MakeCurrent()
	{
		m_GfxContext->MakeCurrent();
	}

	HGLRC Renderer::GetRenderContext()
	{
		return (HGLRC)m_GfxContext->GetContext();
	}

}