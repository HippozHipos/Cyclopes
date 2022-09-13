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

	void Renderer::SetTargetWindow(const Cyc_String& nameId)
	{
		m_GfxContext->MakeCurrent(nameId);
	}

	void Renderer::SwapBuffers(const Cyc_String& nameId)
	{
		m_GfxContext->SwapBuffers(nameId);
	}

	Window* Renderer::GetTargetWindow() const
	{
		return m_GfxContext->GetTargetWindow();;
	}

	void Renderer::PushWindow(Window* window)
	{
		m_GfxContext->PushWindow(window);
	}

	void Renderer::OnDestory()
	{
		m_GfxContext->OnDestory();
	}

}