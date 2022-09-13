#include "Cycpch.h"
#include "GraphicsContext.h"

#include "Cyclopes/Platform/OpenGl/OpenGLContext.h"

namespace cyc {

	Cyc_Scoped<GraphicsContext> GraphicsContext::Create()
	{
		return std::make_unique<OpenGLContext>();
	}

}