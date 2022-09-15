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
            CYC_CORE_ERROR("OpenGL Error\nType: {0}\nSeverity: {1}\nMessage: {2}", 
                type, severity, message);
        }
    }
}