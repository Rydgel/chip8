#include <chip8/Constants.hpp>
#include "Chip8Renderer.hpp"

Chip8Renderer::Chip8Renderer()
: shader_("shaders/cube.vert", "shaders/cube.frag")
{

}

Chip8Renderer::~Chip8Renderer()
{
    unbind();
}

void Chip8Renderer::clear()
{
    glClearColor(52.0f / 255.0f, 73.0f / 255.0f, 94.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Chip8Renderer::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition)
{
    shader_.setUniform("model", model);
    shader_.setUniform("view", view);
    shader_.setUniform("projection", projection);
    // lights and stuff
    glm::vec3 objectColorLoc(149.0f / 255.0f, 165.0f / 255.0f, 166.0f / 255.0f);
    glm::vec3 lightPosLoc(Constants::WIDTH / 2, 0.0f, 2.0f);
    glm::vec3 lightColorLoc(1.0f, 1.0f, 1.0f);
    shader_.setUniform("objectColor", objectColorLoc);
    shader_.setUniform("lightColor", lightColorLoc);
    shader_.setUniform("lightPos", lightPosLoc);
    shader_.setUniform("viewPos", cameraPosition);

    cubemodel_.draw();
}

void Chip8Renderer::drawPixels(std::array<uint8_t, NPIXELS> & pixels, Camera & camera)
{
    auto view = camera.getViewMatrix();
    auto projection = glm::perspective(camera.getZoom(), 2.0f, 0.1f, 500.0f);
    auto cameraPosition = camera.getPosition();

    int i = 0;
    for (const auto & pixel : pixels) {
        if (pixel > 0) {
            auto pos = glm::vec3(i % WIDTH, -i / WIDTH, -40);
            glm::mat4 model;
            model = glm::translate(model, pos);
            draw(model, view, projection, cameraPosition);
        }
        i ++;
    }
}

void Chip8Renderer::bind()
{
    shader_.bind();
    cubemodel_.upload();
}

void Chip8Renderer::unbind()
{
    shader_.unbind();
    cubemodel_.cleanup();
}