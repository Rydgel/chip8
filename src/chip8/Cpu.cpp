#include "Cpu.hpp"

Cpu::Cpu(Memory & memory)
: memory_(memory)
{
    makeSound = true;
    drawFlag = true;
    key.fill(0);

    opcode_ = 0;
    registers_.fill(0);
    index_ = 0;
    pc_ = 0x200;
    pixels_.fill(0);
    timerDelay_ = 0;
    timerSound_ = 0;
    stack_.fill(0);
    sp_ = 0;
}

void Cpu::fetchOpcode()
{
    auto currentPc = static_cast<uint8_t>(pc_);
    opcode_ = memory_.fetchOpcode(currentPc);
}

void Cpu::executeOpcode()
{
    switch (opcode_ & 0xF00) {
        default: break;
        case 0x0000:
            switch (opcode_) {
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
    if (timerDelay_ > 0) {
        timerDelay_ -= 1;
    }

    makeSound = false;
    if (timerSound_ > 0) {
        makeSound = timerSound_ == 1;
        timerSound_ -= 1;
    }
}

void Cpu::clearScreen()
{
    pixels_.fill(0);
    drawFlag = true;
    pc_ += 2;
}

void Cpu::returnSubroutine()
{
    sp_ -= 1;
    pc_ = stack_[sp_];
    pc_ += 2;
}

void Cpu::jumpToAdress()
{
    pc_ = static_cast<uint16_t>(opcode_ & 0x0FFF);
}
