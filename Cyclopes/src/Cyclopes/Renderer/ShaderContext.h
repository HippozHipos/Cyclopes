#pragma once

#include "Cyclopes/Core/Base.h"

namespace cyc {

	class ShaderContext
	{
	public:
		static Cyc_Scoped<ShaderContext> Create();
		virtual void Init(const char* vertexShader, const char* fragmentShader) = 0;
		virtual void Use() = 0;
		virtual void Destroy() = 0;
	};
}
