#ifndef CHIP8_CHIP8_HPP
#define CHIP8_CHIP8_HPP


#include <string>
#include "chip8/Memory.hpp"
#include "chip8/Cpu.hpp"

struct Chip8
{
    Chip8() : cpu_(memory_) {};
    ~Chip8() = default;

    void loadRomFromFile(const std::string filePath);
    void run();

private:

    Memory memory_;
    Cpu cpu_;
};


#endif //CHIP8_CHIP8_HPP
