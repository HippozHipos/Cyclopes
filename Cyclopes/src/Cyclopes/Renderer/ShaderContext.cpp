#include "Cycpch.h"
#include "ShaderContext.h"
#include "Cyclopes/Platform/OpenGl/OpenGLShader.h"

namespace cyc {

	Cyc_Scoped<ShaderContext> ShaderContext::Create()
	{
		return Cyc_MakeScoped<OpenGLShader>();
	}
}