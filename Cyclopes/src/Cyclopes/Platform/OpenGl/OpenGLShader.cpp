#include "Cycpch.h"
#include "OpenGLShader.h"
#include "OpenGLError.h"

#include <glm/gtc/type_ptr.hpp>
#include <Cyclopes/Core/Log.h>

namespace cyc {

	unsigned int OpenGLShader::MakeVertexShader(const char* source)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeVertexShader] glCreateShader");
		uint32_t vs = glCreateShader(GL_VERTEX_SHADER);

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeVertexShader] glShaderSource");
		glShaderSource(vs, 1, &source, NULL);

		return vs;
	}

	unsigned int OpenGLShader::MakeFragmentShader(const char* source)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeFragmentShader] glCreateShader");
		uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER); 

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeFragmentShader] glShaderSource");
		glShaderSource(fs, 1, &source, NULL);

		return fs;
	}

	void OpenGLShader::CompileShaders(uint32_t vs, uint32_t fs)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CompileShaders] glCompileShader(vs)");
		glCompileShader(vs);
		CHECK_SHADER_COMPILATION(vs);


		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CompileShaders] glCompileShader(fs)");
		glCompileShader(fs);
		CHECK_SHADER_COMPILATION(fs);
	}

	void OpenGLShader::CreateProgram(uint32_t vs, uint32_t fs)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CreateProgram] glCreateProgram");
		m_Program = glCreateProgram();

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CreateProgram] glAttachShader");
		glAttachShader(m_Program, vs);

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CreateProgram] glAttachShader");
		glAttachShader(m_Program, fs);
	}
	
	void OpenGLShader::LinkProgram(uint32_t vs, uint32_t fs)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::LinkProgram] glLinkProgram");
		glLinkProgram(m_Program);

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::LinkProgram] glDeleteShader(vs)");
		glDeleteShader(vs);

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::LinkProgram] glDeleteShader(fs)");
		glDeleteShader(fs);
	}

	void OpenGLShader::Init(const char* vertexSource, const char* fragmentSource)
	{
		uint32_t vs = MakeVertexShader(vertexSource);
		uint32_t fs = MakeFragmentShader(fragmentSource);

		CompileShaders(vs, fs);
		CreateProgram(vs, fs);
		LinkProgram(vs, fs);
	}

	void OpenGLShader::Use()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::Use] glUseProgram");
		glUseProgram(m_Program);
	}

	void OpenGLShader::Destroy()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::Delete] glDeleteProgram");
		glDeleteProgram(m_Program);
	}


	void OpenGLShader::SetMat4f(const Cyc_String& name, const glm::mat4& matrix)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::SetMat4f] glGetUniformLocation");
		GLint location = glGetUniformLocation(m_Program, name.c_str());

		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::SetMat4f] glUniformMatrix4fv");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}