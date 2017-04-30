#include "Buffer.hpp"

Buffer::Buffer(GLenum type)
: type_(type)
{
    glGenBuffers(1, &id_);
}

Buffer::~Buffer()
{
    if (id_ != 0) {
        glDeleteBuffers(1, &id_);
    }
}

Buffer::Buffer(Buffer && other) noexcept
: id_(other.id_)
, type_(other.type_)
{
    other.id_ = 0;
}

Buffer & Buffer::operator=(Buffer && other) noexcept
{
    id_ = other.id_;
    type_ = other.type_;

    other.id_ = 0;
    return *this;
}

void Buffer::bind() const
{
    glBindBuffer(type_, id_);
}

void Buffer::unbind() const
{
    glBindBuffer(type_, 0);
}