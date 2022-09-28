#include "Cycpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace cyc {

	void OpenGLVertexArray::Init()
	{
		glGenVertexArrays(1, &m_GlBufferId);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_GlBufferId);
	}

	void OpenGLVertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_GlBufferId);
	}
}