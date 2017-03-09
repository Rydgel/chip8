#ifndef CHIP8_CHIP8_HPP
#define CHIP8_CHIP8_HPP


#include "chip8/Memory.hpp"
#include "chip8/Cpu.hpp"

struct Chip8
{
    Chip8() : cpu_(memory_) {};
    ~Chip8() = default;

    void emulateCycle();

private:

    Memory memory_;
    Cpu cpu_;
};


#endif //CHIP8_CHIP8_HPP
