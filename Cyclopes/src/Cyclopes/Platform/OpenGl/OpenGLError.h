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

    void SetOpenGlErrorMsgCallback(const char* function);
}

#ifndef CYC_OPENGL_ERROR_CALLBACK
    #if defined(CYC_DEBUG) || defined(CYC_RELEASE)
        #define CYC_OPENGL_ERROR_CALLBACK(fnName) SetOpenGlErrorMsgCallback(fnName)
    #else
        #define CYC_OPENGL_ERROR_CALLBACK(fnName)
    #endif
#endif
