#include "OpenGLError.hpp"

const char* OpenGLError::glErrorString(GLenum err)
{
    switch (err) {
        case GL_INVALID_ENUM: return "Invalid Enum";
        case GL_INVALID_VALUE: return "Invalid Value";
        case GL_INVALID_OPERATION: return "Invalid Operation";
        case GL_STACK_OVERFLOW: return "Stack Overflow";
        case GL_STACK_UNDERFLOW: return "Stack Underflow";
        case GL_OUT_OF_MEMORY: return "Out of Memory";
        case GL_TABLE_TOO_LARGE: return "Table too Large";
        default: return "Unknown Error";
    }
}

bool OpenGLError::isOpenGLError()
{
    bool isError = false;
    GLenum errCode;
    const char *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR) {
        isError = true;
        errString = glErrorString(errCode);
        std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
    }

    return isError;
}

void OpenGLError::checkOpenGLError(std::string error)
{
    if (isOpenGLError()) {
        std::cerr << error << std::endl;
        exit (EXIT_FAILURE);
    }
}