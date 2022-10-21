#pragma once

#include "Cyclopes/Core/Base.h"
#include "glad/glad.h"

namespace cyc {

    void GLAPIENTRY OpenGLErrorMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam);

    void SetOpenGlErrorMsgCallback(const char* msg);

    void CheckShaderCompilationSuccess(std::uint32_t shader);
}

#ifndef CYC_OPENGL_ERROR_CALLBACK
    #if defined(CYC_DEBUG) || defined(CYC_RELEASE)
        #define CYC_OPENGL_ERROR_CALLBACK(msg) SetOpenGlErrorMsgCallback(msg)
    #else
        #define CYC_OPENGL_ERROR_CALLBACK(fnName)
    #endif
#endif

#if defined(CYC_DEBUG) || defined(CYC_RELEASE)
    #define CHECK_SHADER_COMPILATION(shader) CheckShaderCompilationSuccess(shader)
#else
    #define CHECK_SHADER_COMPILATION(shader)
#endif
