#ifndef CHIP8_ARRAYBUFFER_HPP
#define CHIP8_ARRAYBUFFER_HPP

#include "Buffer.hpp"

struct ArrayBuffer : public Buffer
{
    ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {};
};


#endif //CHIP8_ARRAYBUFFER_HPP
