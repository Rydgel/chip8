#ifndef CHIP8_CHIP8RENDERER_HPP
#define CHIP8_CHIP8RENDERER_HPP

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <graphics/opengl/Shader.hpp>
#include <chip8/Constants.hpp>
#include <array>
#include "CubeModel.hpp"
#include "Camera.hpp"

using namespace Constants;

struct Chip8Renderer
{
    Chip8Renderer();
    ~Chip8Renderer();

    void clear();
    void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition);
    void drawPixels(std::array<uint8_t, NPIXELS> & pixels, Camera & camera);
    void bind();
    void unbind();

private:

    CubeModel cubemodel_;
    Shader shader_;
};


#endif //CHIP8_CHIP8RENDERER_HPP
