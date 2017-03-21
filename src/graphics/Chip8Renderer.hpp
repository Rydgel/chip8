#ifndef CHIP8_CHIP8RENDERER_HPP
#define CHIP8_CHIP8RENDERER_HPP

#include <glm/mat4x4.hpp>
#include <graphics/opengl/Shader.hpp>
#include "CubeModel.hpp"

struct Chip8Renderer
{
    Chip8Renderer();
    ~Chip8Renderer();

    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);
    void bind();
    void unbind();

private:

    CubeModel cubemodel_;
    Shader shader_;
};


#endif //CHIP8_CHIP8RENDERER_HPP
