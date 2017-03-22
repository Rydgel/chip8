#ifndef CHIP8_CHIP8_HPP
#define CHIP8_CHIP8_HPP


#include <string>
#include <graphics/Window.hpp>
#include <graphics/Timer.hpp>
#include <audio/Sound.hpp>
#include <graphics/Chip8Renderer.hpp>
#include <graphics/Camera.hpp>
#include "chip8/Memory.hpp"
#include "chip8/Cpu.hpp"

struct Chip8
{
    Chip8();
    ~Chip8();

    void loadRomFromFile(const std::string filePath);
    void run();

private:

    Memory memory_;
    Cpu cpu_;
    Window window_;
    Sound sound_;
    Timer timer_;
    // graphics
    Chip8Renderer renderer_;
    Camera camera_;
    std::array<uint8_t, NPIXELS> buffering_ {};
};


#endif //CHIP8_CHIP8_HPP
