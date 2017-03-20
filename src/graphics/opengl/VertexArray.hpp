#ifndef CHIP8_VERTEXARRAY_HPP
#define CHIP8_VERTEXARRAY_HPP

#include <glad.h>

struct VertexArray
{
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray & vertexArray) = delete;
    VertexArray(VertexArray && vertexArray);
    VertexArray & operator=(VertexArray && vertexArray);

    void bind() const;
    void unbind() const;

private:

    GLuint id_ = 0;
};


#endif //CHIP8_VERTEXARRAY_HPP
