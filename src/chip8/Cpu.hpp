#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP


#include "Memory.hpp"

using namespace Constants;

struct Cpu
{
    uint16_t opcode;
    Memory & memory;
    std::array<uint8_t, NREG> registers;
    uint16_t index;
    uint16_t pc;
    std::array<uint8_t, NPIXELS> pixels;
    uint8_t timerDelay;
    uint8_t timerSound;
    std::array<uint16_t, 16> stack;
    uint16_t sp;

    bool drawFlag;
    bool makeSound;
    std::array<uint8_t, 16> key;

    Cpu(Memory & memory);
    ~Cpu() = default;
    friend std::ostream & operator <<(std::ostream& outputStream, const Cpu & c);

    void emulateCycle();
private:

    void fetchOpcode();
    void executeOpcode();
    void updateTimers();

    void clearScreen();
    void returnSubroutine();
    void jumpToAdress();
    void executeSubroutine();
    void skipIfVXIsNN();
    void skipIfVXIsNotNN();
    void skipIfRegXIsRegY();
    void setRegXToNN();
    void addNNToRegX();
    void setRegXToRegY();
    void setRegXToRegXOrRegY();
    void setRegXToRegXAndRegY();
    void setRegXToRegXXorRegY();
};


#endif //CHIP8_CPU_HPP
