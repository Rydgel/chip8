#include <chip8/Rom.hpp>
#include <thread>
#include <iostream>
#include <fmt/format.h>
#include "Chip8.hpp"

Chip8::Chip8()
: cpu_(memory_)
, window_(inputManager_, 1280, 640, "Chip8 emulator")
, camera_(inputManager_)
{
    timer_.init();
    renderer_.bind();
    buffering_.fill(0);
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

        if (inputManager_.getKeyState(GLFW_KEY_ESCAPE)) {
            window_.closeWindow();
        }

        cpu_.key = inputManager_.toChip8KeyStates();
        cpu_.emulateCycle(dt);
        camera_.update(dt);

        timer_.updateUPS();

        if (cpu_.drawFlag) {
            buffering_ = cpu_.pixels;
            cpu_.drawFlag = false;
        }

        renderer_.clear();
        renderer_.drawPixels(buffering_, camera_);

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
