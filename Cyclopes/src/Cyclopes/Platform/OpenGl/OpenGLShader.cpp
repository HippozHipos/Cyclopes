#include "Cycpch.h"
#include "OpenGLShader.h"
#include "OpenGLError.h"

namespace cyc {

	unsigned int OpenGLShader::MakeVertexShader(const char* source)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeVertexShader]");

		uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &source, NULL);
		return vs;
	}

	unsigned int OpenGLShader::MakeFragmentShader(const char* source)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::MakeFragmentShader]");

		uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &source, NULL);
		return fs;
	}

	void OpenGLShader::CompileShaders(uint32_t vs, uint32_t fs)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CompileShaders]");

		glCompileShader(vs);
		glCompileShader(fs);
	}

	void OpenGLShader::CreateProgram(uint32_t vs, uint32_t fs)
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::CreateProgram]");

		m_Program = glCreateProgram();
		glAttachShader(m_Program, vs);
		glAttachShader(m_Program, fs);
	}
	
	void OpenGLShader::LinkProgram(uint32_t vs, uint32_t fs)
	{
		glLinkProgram(m_Program);
		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	void OpenGLShader::OnInit(const char* vertexSource, const char* fragmentSource)
	{
		uint32_t vs = MakeVertexShader(vertexSource);
		uint32_t fs = MakeFragmentShader(fragmentSource);

		CompileShaders(vs, fs);
		CreateProgram(vs, fs);
		LinkProgram(vs, fs);
	}

	void OpenGLShader::Use()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::Use]");

		glUseProgram(m_Program);
	}

	void OpenGLShader::OnDestroy()
	{
		CYC_OPENGL_ERROR_CALLBACK("[OpenGLShader::Delete]");

		glDeleteProgram(m_Program);
	}

}