#pragma once

#include "Cyclopes/Core/Base.h"
#include "glm/glm.hpp"

namespace cyc {

	class Shader
	{
	public:
		static Cyc_Scoped<Shader> Create();
		virtual void Init(const char* vertexShader, const char* fragmentShader) = 0;
		virtual void Use() = 0;
		virtual void Destroy() = 0;
		virtual void SetMat4f(const Cyc_String& name, const glm::mat4& value) = 0;
	};
}
