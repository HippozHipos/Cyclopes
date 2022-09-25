#pragma once

#include <string>
#include <glad/glad.h>

namespace cyc {

	class OpenGLShader
	{
	public:
		void Init(const char* vertexSource, const char* fragmentSource);
		void Use();
		void Delete();

	private:
		uint32_t MakeVertexShader(const char* source);
		uint32_t MakeFragmentShader(const char* source);
		void CompileShaders(uint32_t vs, uint32_t fs);
		void CreateProgram(uint32_t vs, uint32_t fs);

	private:
		uint32_t m_Program = 0;
	};
}
