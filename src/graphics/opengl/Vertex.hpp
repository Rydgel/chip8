#ifndef CHIP8_VERTEX_HPP
#define CHIP8_VERTEX_HPP

#include <glm/glm.hpp>

struct Vertex
{
    // Position
    glm::vec3 position;
    // Normal
    glm::vec3 normal;
    // TexCoords
    glm::vec3 texCoords;
};

#endif //CHIP8_VERTEX_HPP
