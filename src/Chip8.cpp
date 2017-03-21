#include <chip8/Rom.hpp>
#include <thread>
#include <iostream>
#include <fmt/format.h>
#include "Chip8.hpp"

Chip8::Chip8()
: cpu_(memory_)
, window_(1280, 640, "Chip8 emulator")
{
    timer_.init();
    renderer_.bind();
}

Chip8::~Chip8()
{
    renderer_.unbind();
}

void Chip8::loadRomFromFile(const std::string filePath)
{
    Rom rom(filePath);
    memory_.loadBinary(rom.binaryData);
}

void Chip8::run()
{
    while (window_.isOpen()) {
        const float dt = timer_.getDelta();

        window_.pollEvents();

        cpu_.emulateCycle();
        camera_.update(dt);

        timer_.updateUPS();

        if (cpu_.drawFlag) {
            // todo find a way to only draw when needed without weird clippings
            // todo with framebuffer maybe?
            cpu_.drawFlag = false;
        }

        glClearColor(52.0f / 255.0f, 73.0f / 255.0f, 94.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto view = camera_.getViewMatrix();
        auto projection = glm::perspective(camera_.getZoom(), 2.0f, 0.1f, 500.0f);
        auto cameraPosition = camera_.getPosition();

        int i = 0;
        for (const auto & pixel : cpu_.pixels) {
            if (pixel > 0) {
                auto pos = glm::vec3(i % WIDTH, -i / WIDTH, -40);
                glm::mat4 model;
                model = glm::translate(model, pos);
                renderer_.draw(model, view, projection, cameraPosition);
            }
            i ++;
        }

        if (cpu_.makeSound) {
            sound_.playBeep();
            cpu_.makeSound = false;
        }

        timer_.updateFPS();
        timer_.update();

        const auto fpsTitle = fmt::format("Chip8 emulator • FPS: {}", timer_.getFPS());
        window_.changeTitle(fpsTitle.c_str());

        window_.swapBuffers();
    }
}
