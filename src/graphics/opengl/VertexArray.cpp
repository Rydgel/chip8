#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id_);
}

VertexArray::~VertexArray()
{
    if (id_ != 0) {
        glDeleteVertexArrays(1, &id_);
    }
}

VertexArray::VertexArray(VertexArray && vertexArray) noexcept
: id_(vertexArray.id_)
{
    vertexArray.id_ = 0;
}

VertexArray & VertexArray::operator=(VertexArray && vertexArray) noexcept
{
    id_ = vertexArray.id_;
    vertexArray.id_ = 0;
    return *this;
}

void VertexArray::bind() const
{
    glBindVertexArray(id_);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}