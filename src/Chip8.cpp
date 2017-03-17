#include <chip8/Rom.hpp>
#include <thread>
#include <iostream>
#include <fmt/format.h>

#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#endif

#include "Chip8.hpp"

Chip8::Chip8()
: cpu_(memory_)
, window_(1280, 640, "Chip8 emulator")
{
    timer_.init();

    // todo remove test
    ALCdevice *device;
    device = alcOpenDevice(nullptr);
    if (!device) { }
    alcCloseDevice(device);
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

        timer_.updateUPS();

        if (cpu_.drawFlag) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            std::cout << cpu_ << std::endl;
            cpu_.drawFlag = false;
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
