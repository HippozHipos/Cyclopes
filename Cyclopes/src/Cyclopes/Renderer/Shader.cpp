#include "Cycpch.h"
#include "Shader.h"
#include "Cyclopes/Platform/OpenGl/OpenGLShader.h"

namespace cyc {

	Cyc_Scoped<Shader> Shader::Create()
	{
		return Cyc_MakeScoped<OpenGLShader>();
	}
}