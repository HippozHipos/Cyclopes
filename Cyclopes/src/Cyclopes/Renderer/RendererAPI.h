#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace cyc {

	class RendererAPI
	{
		virtual void DrawIndexedVertices(const VertexBuffer* vb, const IndexBuffer* ib) = 0;
	};

}