#ifndef CHIP8_MESH_HPP
#define CHIP8_MESH_HPP

#include <vector>
#include <glad.h>
#include <glm/vec3.hpp>
#include "VertexAttribute.hpp"

struct Mesh
{
    void addPosition(glm::vec3 position);
    void addIndices(GLuint indice);
    void addNormal(glm::vec3 normal);
    void addUvs(glm::vec2 uv);
    void addColors(glm::vec3 color);

    const std::vector<glm::vec3> getPositions() const;
    const std::vector<GLuint> getIndices() const;
    const std::vector<glm::vec3> getNormals() const;
    const std::vector<glm::vec2> getUvs() const;
    const std::vector<glm::vec3> getColors() const;
    // lock the mesh when uploaded to graphic card
    void lock();

private:

    std::vector<glm::vec3> positions_ {};
    std::vector<GLuint> indices_ {};
    std::vector<glm::vec3> normals_ {};
    std::vector<glm::vec2> uvs_ {};
    std::vector<glm::vec3> colors_ {};
    std::vector<GLfloat> vertices_ {};

    bool isModified_ = true;
};


#endif //CHIP8_MESH_HPP
