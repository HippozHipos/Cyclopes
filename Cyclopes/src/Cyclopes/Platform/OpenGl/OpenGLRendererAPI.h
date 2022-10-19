#pragma once

#include "Cyclopes/Renderer/RendererAPI.h"
#include "glad/glad.h"

namespace cyc {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear(float r, float g, float b, float a) const override;
		void DrawIndexedVertices(const IndexBuffer* ib) const override;
	};

}

