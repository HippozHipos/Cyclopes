#include "Cycpch.h"
#include "OpenGLIndexBuffer.h"

#include "glad/glad.h"

namespace cyc {
	OpenGLIndexBuffer::OpenGLIndexBuffer()
	{
		m_IndexBuffer = Cyc_MakeScoped<Cyc_Vector<int>>();
	}

	void OpenGLIndexBuffer::SetIndices(const Cyc_Vector<int>& indices)
	{
		*m_IndexBuffer = indices;
	}

	void OpenGLIndexBuffer::Init()
	{
		glGenBuffers(1, &m_GlBufferId);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GlBufferId);
	}

	void OpenGLIndexBuffer::BufferData(bool staticDraw)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_IndexBuffer->size(), m_IndexBuffer->data(), staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void OpenGLIndexBuffer::DestroyIndexBuffer()
	{
		m_IndexBuffer.reset();
	}

	void OpenGLIndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_GlBufferId);
		m_IndexBuffer.reset();

	}

	
}