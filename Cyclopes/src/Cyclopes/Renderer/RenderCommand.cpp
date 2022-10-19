#include "Cycpch.h"
#include "RenderCommand.h"

#include "Cyclopes/Core/Assert.h"

#include <GLAD/glad.h>

namespace cyc {

	Cyc_Scoped<RendererAPI> RenderCommand::m_RendererAPI;

	void RenderCommand::SetRendererAPI()
	{
#ifdef CYC_PLATFORM_WINDOWS
		m_RendererAPI = RendererAPI::Create(RendererAPI::Type::OPENGL); return;//change to dx when dx is implemented
#endif

		//fallback to opengl if no other rendering api fits the os
		m_RendererAPI = RendererAPI::Create(RendererAPI::Type::OPENGL);
	}

	void RenderCommand::Clear(float r, float g, float b, float a)
	{
		CYC_CORE_ASSERT(m_RendererAPI != nullptr, "[RenderCommand::Clear] Renderer API not set");
		m_RendererAPI->Clear(r, g, b, a);
	}

	void RenderCommand::DrawIndexedVertices(const IndexBuffer* ib)
	{
		CYC_CORE_ASSERT(m_RendererAPI != nullptr, "[RenderCommand::Clear] Renderer API not set");
		m_RendererAPI->DrawIndexedVertices(ib);
	}
}