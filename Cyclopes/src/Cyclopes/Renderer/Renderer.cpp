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

	void Renderer::SetSwapInterval(int interval)
	{
		m_GfxContext->SetSwapInterval(interval);
	}

	void Renderer::OnDestroy()
	{
		m_GfxContext->OnDestroy();
	}

	void Renderer::MakeCurrent()
	{
		m_GfxContext->MakeCurrent();
	}

	void* Renderer::GetRenderContext()
	{
		return m_GfxContext->GetContext();
	}

	void Renderer::SetViewport(float x, float y, float width, float height)
	{
		m_GfxContext->SetViewport(x, y, width, height);
	}

}