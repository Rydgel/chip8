#ifndef CHIP8_CUBEMODEL_HPP
#define CHIP8_CUBEMODEL_HPP

#include <graphics/opengl/Mesh.hpp>
#include <graphics/opengl/VertexArray.hpp>
#include <graphics/opengl/ArrayBuffer.hpp>
#include <graphics/opengl/IndexBuffer.hpp>

struct CubeModel
{
    CubeModel();
    ~CubeModel();


    void upload();
    void draw();
    void cleanup();

    Mesh mesh;
    VertexArray vertexArray;
    ArrayBuffer positionsBuffer;
    ArrayBuffer colorsBuffer;
    ArrayBuffer normalsBuffer;
    IndexBuffer indicesBuffer;

private:

    void addVertices();
    void addIndices();
    void addColors();
    void addNormals();
};


#endif //CHIP8_CUBEMODEL_HPP
