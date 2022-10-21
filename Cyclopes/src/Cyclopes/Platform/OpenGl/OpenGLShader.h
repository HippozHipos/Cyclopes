#pragma once

#include <string>
#include <glad/glad.h>
#include "Cyclopes/Renderer/Shader.h"

namespace cyc {

	class OpenGLShader : public Shader
	{
	public:
		void Init(const char* vertexSource, const char* fragmentSource) override;
		void Use() override;
		void Destroy() override;

	private:
		uint32_t MakeVertexShader(const char* source);
		uint32_t MakeFragmentShader(const char* source);
		void CompileShaders(uint32_t vs, uint32_t fs);
		void CreateProgram(uint32_t vs, uint32_t fs);
		void LinkProgram(uint32_t vs, uint32_t fs);

	public:
		void SetMat4f(const Cyc_String& name, const glm::mat4& value) override;

	private:
		uint32_t m_Program = 0;
	};
}
