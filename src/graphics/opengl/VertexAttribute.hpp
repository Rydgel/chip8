#ifndef CHIP8_VERTEX_HPP
#define CHIP8_VERTEX_HPP

#include <glm/glm.hpp>

enum VertexAttribute
{
    Position = 0x1,
    TexCoords = 0x2,
    Normal = 0x4,
    Tangent = 0x8
};

#endif //CHIP8_VERTEX_HPP
