#pragma once

#include "Cyclopes/Core/Base.h"
#include "OpenGLError.h"

#include <vector>
#include <glad/glad.h>

namespace cyc {

	template<class Type>
	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer()
		{
			m_VertexBuffer = Cyc_MakeScoped<Cyc_Vector<Type>>();
		}

	public:
		void Init()
		{
			CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Init]");

			glGenBuffers(1, &m_GlBufferId);
		}

		void SetVertices(const Cyc_Vector<Type>& vertices)
		{
			*m_VertexBuffer = vertices;
		}

		void BufferData(bool staticDraw = true) const
		{
			CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::BufferData]");

			glBufferData(GL_ARRAY_BUFFER, sizeof(Type) * m_VertexBuffer->size(), m_VertexBuffer->data(), staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
		}

		void Bind() const
		{
			CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Bind]");

			glBindBuffer(GL_ARRAY_BUFFER, m_GlBufferId);
		}

	public:
		void DestroyCPUVertexBuffer()
		{
			m_VertexBuffer.reset();
		}

		void Destroy()
		{
			CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Destroy]");

			glDeleteBuffers(1, &m_GlBufferId);
			m_VertexBuffer.reset();
		}

	private:
		Cyc_Scoped<Cyc_Vector<Type>> m_VertexBuffer;
		uint32_t m_GlBufferId = 0;
	};

}

