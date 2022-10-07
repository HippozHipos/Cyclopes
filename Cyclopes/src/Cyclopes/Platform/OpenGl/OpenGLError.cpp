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
}