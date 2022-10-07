#include "Cycpch.h"
#include "RenderCommand.h"

#include <GLAD/glad.h>

namespace cyc {

	void RenderCommand::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

}