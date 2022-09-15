#pragma once

#include "glad/glad.h"

namespace cyc {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);
}
