#include "Cycpch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLError.h"

#include "glad/glad.h"

namespace cyc {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		m_LayoutBuffer = Cyc_MakeScoped<Cyc_Vector<Layout>>();
	}

	void OpenGLVertexArray::Use()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::Use]");

		Bind();
		int i = 0;
		for (auto& vl : *m_LayoutBuffer)
		{
			switch ((int)vl.type)
			{
				case (int)LayoutType::INT: glVertexAttribPointer(vl.index, vl.size, GL_INT, vl.normalize, vl.stride, (void*)vl.offset); break;
				case (int)LayoutType::FLOAT: glVertexAttribPointer(vl.index, vl.size, GL_FLOAT, vl.normalize, vl.stride, (void*)vl.offset); break;
				case (int)LayoutType::DOUBLE: glVertexAttribPointer(vl.index, vl.size, GL_DOUBLE , vl.normalize, vl.stride, (void*)vl.offset); break;
				case (int)LayoutType::SHORT: glVertexAttribPointer(vl.index, vl.size, GL_SHORT, vl.normalize, vl.stride, (void*)vl.offset); break;
			}
			glEnableVertexAttribArray(i++);
		}
	}

	void OpenGLVertexArray::Init()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::Init]");

		glGenVertexArrays(1, &m_GlBufferId);
	}

	void OpenGLVertexArray::Bind()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::Bind]");

		glBindVertexArray(m_GlBufferId);
	}

	void OpenGLVertexArray::EnableAttribute(int i)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::EnableAttribute]");

		CYC_CORE_ASSERT(i < m_LayoutBuffer->size(), 
			"Index out of range. Valid Index = 0 to {0}", m_LayoutBuffer->size() - 1);

		glEnableVertexAttribArray(i);
	}

	void OpenGLVertexArray::DisableAttribute(int i)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::DisableAttribute]");

		CYC_CORE_ASSERT(i < m_LayoutBuffer->size(),
			"Index out of range. Valid Index = 0 to {0}", m_LayoutBuffer->size() - 1);

		glDisableVertexAttribArray(i);
	}

	void OpenGLVertexArray::Destroy()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLVertexArray::Destroy]");

		glDeleteVertexArrays(1, &m_GlBufferId);
		m_LayoutBuffer.reset();
	}
}