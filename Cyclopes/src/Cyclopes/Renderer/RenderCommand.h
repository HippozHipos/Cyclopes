#pragma once

#include "RendererAPI.h"

namespace cyc {

	class RenderCommand
	{
	public:
		static void SetRendererAPI();

	public:
		static void Clear(float r, float g, float b, float a);
		static void DrawIndexedVertices(const IndexBuffer* ib);

	private:
		static Cyc_Scoped<RendererAPI> m_RendererAPI;
	};
}
