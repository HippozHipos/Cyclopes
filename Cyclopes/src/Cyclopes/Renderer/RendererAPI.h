#pragma once

#include "Cyclopes/Core/Base.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace cyc {

	class RendererAPI
	{
	public:
		enum class Type
		{
			OPENGL,
			DX12
		};

	public:
		static Cyc_Scoped<RendererAPI> Create(Type type);

	public:
		virtual void Clear(float r, float g, float b, float a) const = 0;
		virtual void DrawIndexedVertices(const IndexBuffer* ib) const = 0;

	private:
		static Type m_Type;
	};

}