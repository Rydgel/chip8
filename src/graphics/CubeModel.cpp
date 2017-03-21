#include "CubeModel.hpp"

CubeModel::CubeModel()
{
    addVertices();
    addIndices();
    addColors();
    addNormals();
}

CubeModel::~CubeModel()
{
    cleanup();
}

void CubeModel::upload()
{
    vertexArray.bind();

    positionsBuffer.bind();
    positionsBuffer.setData(mesh.getPositions(), Usage::Static);
    normalsBuffer.bind();
    normalsBuffer.setData(mesh.getNormals(), Usage::Static);
    colorsBuffer.bind();
    colorsBuffer.setData(mesh.getColors(), Usage::Static);
    indicesBuffer.bind();
    indicesBuffer.setData(mesh.getIndices(), Usage::Static);

    // todo add data to VertexAttributes normals

    glEnableVertexAttribArray(0);
    positionsBuffer.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(1);
    colorsBuffer.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);

    glEnableVertexAttribArray(2);
    normalsBuffer.bind();
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*) 0);
}

void CubeModel::draw()
{
    indicesBuffer.bind();
    auto indicesSize = static_cast<GLsizei>(mesh.getIndices().size());
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    indicesBuffer.unbind();
}

void CubeModel::cleanup()
{
    indicesBuffer.unbind();
    positionsBuffer.unbind();
    vertexArray.unbind();
}

void CubeModel::addVertices()
{
    mesh.addPosition({1, 0, 0});
    mesh.addPosition({0, 0, 0});
    mesh.addPosition({0, 1, 0});
    mesh.addPosition({1, 1, 0});

    mesh.addPosition({1, 0, 1});
    mesh.addPosition({1, 0, 0});
    mesh.addPosition({1, 1, 0});
    mesh.addPosition({1, 1, 1});

    mesh.addPosition({0, 0, 1});
    mesh.addPosition({1, 0, 1});
    mesh.addPosition({1, 1, 1});
    mesh.addPosition({0, 1, 1});

    mesh.addPosition({0, 0, 0});
    mesh.addPosition({0, 0, 1});
    mesh.addPosition({0, 1, 1});
    mesh.addPosition({0, 1, 0});

    mesh.addPosition({0, 1, 1});
    mesh.addPosition({1, 1, 1});
    mesh.addPosition({1, 1, 0});
    mesh.addPosition({0, 1, 0});

    mesh.addPosition({0, 0, 0});
    mesh.addPosition({1, 0, 0});
    mesh.addPosition({1, 0, 1});
    mesh.addPosition({0, 0, 1});
}

void CubeModel::addIndices()
{
    mesh.addIndices(0); mesh.addIndices(1); mesh.addIndices(2);
    mesh.addIndices(2); mesh.addIndices(3); mesh.addIndices(0);

    mesh.addIndices(4); mesh.addIndices(5); mesh.addIndices(6);
    mesh.addIndices(6); mesh.addIndices(7); mesh.addIndices(4);

    mesh.addIndices(8); mesh.addIndices(9); mesh.addIndices(10);
    mesh.addIndices(10); mesh.addIndices(11); mesh.addIndices(8);

    mesh.addIndices(12); mesh.addIndices(13); mesh.addIndices(14);
    mesh.addIndices(14); mesh.addIndices(15); mesh.addIndices(12);

    mesh.addIndices(16); mesh.addIndices(17); mesh.addIndices(18);
    mesh.addIndices(18); mesh.addIndices(19); mesh.addIndices(16);

    mesh.addIndices(20); mesh.addIndices(21); mesh.addIndices(22);
    mesh.addIndices(22); mesh.addIndices(23); mesh.addIndices(20);
}

void CubeModel::addColors()
{
    mesh.addColors({0, 0, 1});
    mesh.addColors({0, 0, 0});
    mesh.addColors({0, 1, 0});
    mesh.addColors({1, 1, 0});

    mesh.addColors({1, 0, 1});
    mesh.addColors({1, 0, 0});
    mesh.addColors({1, 1, 0});
    mesh.addColors({1, 1, 1});

    mesh.addColors({0, 0, 1});
    mesh.addColors({1, 0, 1});
    mesh.addColors({1, 1, 1});
    mesh.addColors({0, 1, 1});

    mesh.addColors({0, 0, 0});
    mesh.addColors({0, 0, 1});
    mesh.addColors({0, 1, 1});
    mesh.addColors({0, 1, 0});

    mesh.addColors({0, 1, 1});
    mesh.addColors({1, 1, 1});
    mesh.addColors({1, 1, 0});
    mesh.addColors({0, 1, 0});

    mesh.addColors({0, 0, 0});
    mesh.addColors({1, 0, 0});
    mesh.addColors({1, 0, 1});
    mesh.addColors({0, 0, 1});
}

void CubeModel::addNormals()
{
    mesh.addNormal({0, 0, -1});
    mesh.addNormal({0, 0, -1});
    mesh.addNormal({0, 0, -1});
    mesh.addNormal({0, 0, -1});

    mesh.addNormal({1, 0, 0});
    mesh.addNormal({1, 0, 0});
    mesh.addNormal({1, 0, 0});
    mesh.addNormal({1, 0, 0});

    mesh.addNormal({0, 0, 1});
    mesh.addNormal({0, 0, 1});
    mesh.addNormal({0, 0, 1});
    mesh.addNormal({0, 0, 1});

    mesh.addNormal({-1, 0, 0});
    mesh.addNormal({-1, 0, 0});
    mesh.addNormal({-1, 0, 0});
    mesh.addNormal({-1, 0, 0});

    mesh.addNormal({0, 1, 0});
    mesh.addNormal({0, 1, 0});
    mesh.addNormal({0, 1, 0});
    mesh.addNormal({0, 1, 0});

    mesh.addNormal({0, -1, 0});
    mesh.addNormal({0, -1, 0});
    mesh.addNormal({0, -1, 0});
    mesh.addNormal({0, -1, 0});
}
