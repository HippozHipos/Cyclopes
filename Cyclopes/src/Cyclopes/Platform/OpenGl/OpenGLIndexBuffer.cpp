#include "Cycpch.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLError.h"

#include "glad/glad.h"

namespace cyc {
	void OpenGLIndexBuffer::Init(std::uint32_t count)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLIndexBuffer::Init]");

		m_Count = count;
		glGenBuffers(1, &m_GlBufferId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLIndexBuffer::Bind]");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_GlBufferId);
	}

	void OpenGLIndexBuffer::BufferData(void* data, long long size, bool staticDraw) const
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLIndexBuffer::BufferData]");

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, staticDraw ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
	}

	void OpenGLIndexBuffer::Destroy()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLIndexBuffer::Destroy]");

		glDeleteBuffers(1, &m_GlBufferId);
	}

	
}