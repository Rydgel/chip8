#include "Cpu.hpp"

Cpu::Cpu(Memory & memory)
: memory(memory)
{
    makeSound = true;
    drawFlag = true;
    key.fill(0);

    opcode = 0;
    registers.fill(0);
    index = 0;
    pc = 0x200;
    pixels.fill(0);
    timerDelay = 0;
    timerSound = 0;
    stack.fill(0);
    sp = 0;
}

void Cpu::fetchOpcode()
{
    opcode = memory.fetchOpcode(pc);
}

void Cpu::executeOpcode()
{
    switch (opcode & 0xF000) {
        default: break;
        case 0x0000:
            switch (opcode) {
                default: break;
                case 0x00E0: clearScreen(); break;
                case 0x00EE: returnSubroutine(); break;
            }
            break;
        case 0x1000: jumpToAdress(); break;
    }
}

void Cpu::updateTimers()
{
    if (timerDelay > 0) {
        timerDelay -= 1;
    }

    makeSound = false;
    if (timerSound > 0) {
        makeSound = timerSound == 1;
        timerSound -= 1;
    }
}

void Cpu::clearScreen()
{
    pixels.fill(0);
    drawFlag = true;
    pc += 2;
}

void Cpu::returnSubroutine()
{
    sp -= 1;
    pc = stack[sp];
    pc += 2;
}

void Cpu::jumpToAdress()
{
    pc = static_cast<uint16_t>(opcode & 0x0FFF);
}
