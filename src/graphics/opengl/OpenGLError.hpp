#ifndef CHIP8_OPENGLERROR_HPP
#define CHIP8_OPENGLERROR_HPP

#include <iostream>
#include <glad.h>

struct OpenGLError
{
    const char* glErrorString(GLenum err);
    bool isOpenGLError();
    void checkOpenGLError(std::string error);
};


#endif //CHIP8_OPENGLERROR_HPP
