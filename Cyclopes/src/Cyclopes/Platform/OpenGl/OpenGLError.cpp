#include "Cycpch.h"
#include "OpenGLError.h"

#include "Cyclopes/Core/Log.h"

namespace cyc {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
    {
        if (type == GL_DEBUG_TYPE_ERROR)
        {
            CYC_CORE_ERROR("OpenGL Error\nFunction: {0}\nType: {1}\nSeverity: {2}\nMessage: {3}\n", 
                (const char*)userParam, type, severity, message);
        }
    }

    void SetOpenGlErrorMsgCallback(const char* msg)
    {
        glDebugMessageCallback(OpenGLErrorMessageCallback, (const char*)msg);
    }

    void CheckShaderCompilationSuccess(std::uint32_t shader)
    {
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            Cyc_Vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog.data());

            CYC_CORE_ERROR(errorLog.data());

            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(shader); // Don't leak the shader.
        }
    }
}