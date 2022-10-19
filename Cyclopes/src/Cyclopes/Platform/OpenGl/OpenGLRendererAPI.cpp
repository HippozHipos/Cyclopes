#include "Cycpch.h"
#include "OpenGLRendererAPI.h"

namespace cyc {

	void OpenGLRendererAPI::Clear(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexedVertices(const IndexBuffer* ib) const
	{
		glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
