#ifndef CHIP8_BUFFER_HPP
#define CHIP8_BUFFER_HPP

#include <glad.h>
#include <vector>

enum class Usage
{
    Static = GL_STATIC_DRAW,
    Dynamic = GL_DYNAMIC_DRAW
};

struct Buffer
{
    explicit Buffer(GLenum type);
    virtual ~Buffer();

    Buffer(const Buffer & buffer) = delete;
    Buffer & operator=(Buffer & other) = delete;
    Buffer(Buffer && other) noexcept;
    Buffer & operator=(Buffer && other) noexcept;

    void bind() const;
    void unbind() const;

    template<typename T>
    void setData(const std::vector<T> & data, Usage usage);

private:

    GLuint id_;
    GLenum type_;
};

template<typename T>
void Buffer::setData(const std::vector<T> & data, Usage usage)
{
    bind();
    glBufferData(type_, sizeof(T) * data.size(), &data[0], static_cast<GLenum>(usage));
    unbind();
}

#endif //CHIP8_BUFFER_HPP
