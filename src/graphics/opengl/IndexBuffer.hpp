#ifndef CHIP8_INDEXBUFFER_H
#define CHIP8_INDEXBUFFER_H

#include "Buffer.hpp"

struct IndexBuffer : public Buffer
{
    IndexBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};

#endif //CHIP8_INDEXBUFFER_H
