#ifndef CHIP8_SHADER_HPP
#define CHIP8_SHADER_HPP

#include <glad.h>
#include <iostream>
#include <glm/glm.hpp>

struct Shader
{
    // Constructor reads and builds the shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // todo add all uniforms type
    // uniform variable settings
    void setUniform(const std::string &name, GLuint x);
    void setUniform(const std::string &name, int x);
    void setUniform(const std::string &name, float x);
    void setUniform(const std::string &name, glm::mat4 trans);
    void setUniform(const std::string &name, glm::vec3 vec);
    // Use the program
    void bind();
    void unbind();

private:

    // The program ID
    GLuint program_;
};

#endif //CHIP8_SHADER_HPP
