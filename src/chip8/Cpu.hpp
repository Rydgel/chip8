#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP


#include "Memory.hpp"

using namespace Constants;

struct Cpu
{
    bool drawFlag;
    bool makeSound;
    std::array<uint8_t, 16> key;

    Cpu(Memory & memory);
    ~Cpu() = default;
    void fetchOpcode();
    void executeOpcode();
    void updateTimers();

    void clearScreen();
    void returnSubroutine();
    void jumpToAdress();

private:

    uint16_t opcode_;
    Memory & memory_;
    std::array<uint8_t, NREG> registers_;
    uint16_t index_;
    uint16_t pc_;
    std::array<uint8_t, NPIXELS> pixels_;
    uint8_t timerDelay_;
    uint8_t timerSound_;
    std::array<uint16_t, 16> stack_;
    uint16_t sp_;
};


#endif //CHIP8_CPU_HPP
