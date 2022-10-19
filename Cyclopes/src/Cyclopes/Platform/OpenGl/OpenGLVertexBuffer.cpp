#include "Cycpch.h"
#include "OpenGLVertexBuffer.h"

namespace cyc {
	 void OpenGLVertexBuffer::Init()
	 {
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Init]");
	
	 	glGenBuffers(1, &m_GlBufferId);
	 }

	void OpenGLVertexBuffer::BufferData(void* data, long long int size, bool staticDraw) const
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::BufferData]");

		glBufferData(GL_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Bind]");

		glBindBuffer(GL_ARRAY_BUFFER, m_GlBufferId);
	}

	void OpenGLVertexBuffer::Destroy()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexBuffer::Destroy]");

		glDeleteBuffers(1, &m_GlBufferId);
	}

}