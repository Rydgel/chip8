#include <iostream>
#include "Cpu.hpp"

static auto notImplemented(const uint16_t opcode)
{
    std::cout << "Error not implemented: " << std::hex << opcode << std::endl;
}

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

std::ostream &operator<<(std::ostream &outputStream, const Cpu &c)
{
    outputStream
            << "Chip8" << std::endl
            << "draw flags: " << std::boolalpha << c.drawFlag << std::endl
            << "opcode: " << std::hex << c.opcode << std::endl
            << "index: " << std::hex << c.index << std::endl
            << "pc: " << std::hex << c.pc << std::endl
            << "t_delay: " << std::hex << c.timerDelay << std::endl
            << "t_sound: " << std::hex << c.timerSound << std::endl
            << "r0: " << std::hex << c.registers[0] << " "
            << "r1: " << std::hex << c.registers[1] << " "
            << "r2: " << std::hex << c.registers[2] << " "
            << "r3: " << std::hex << c.registers[3] << " "
            << "r4: " << std::hex << c.registers[4] << " "
            << "r5: " << std::hex << c.registers[5] << " "
            << "r6: " << std::hex << c.registers[6] << " "
            << "r7: " << std::hex << c.registers[7] << " "
            << "r8: " << std::hex << c.registers[8] << " "
            << "r9: " << std::hex << c.registers[9] << " "
            << "r10: " << std::hex << c.registers[10] << " "
            << "r11: " << std::hex << c.registers[11] << " "
            << "r12: " << std::hex << c.registers[12] << " "
            << "r13: " << std::hex << c.registers[13] << " "
            << "r14: " << std::hex << c.registers[14] << " "
            << "r15: " << std::hex << c.registers[15] << std::endl
            << "sp: " << std::hex << c.sp << std::endl;

    outputStream << "stack: ";
    for (auto &s : c.stack) {
        outputStream << std::hex << s << " ";
    }
    outputStream << std::endl;
    outputStream << "graphics: " << std::endl;
    outputStream << "+----------------------------------------------------------------+" << std::endl;

    for (int i = 0; i < Constants::HEIGHT; i++) {
        for (int j = 0; j < Constants::WIDTH; j++) {
            if (c.pixels[i * 64 + j] == 0) {
                outputStream << " ";
            } else {
                outputStream << "#";
            }
        }
        outputStream << std::endl;
    }

    outputStream << "+----------------------------------------------------------------+" << std::endl;

    return outputStream;
}

void Cpu::fetchOpcode()
{
    opcode = memory.fetchOpcode(pc);
}

void Cpu::executeOpcode()
{
    switch (opcode & 0xF000) {
        default: notImplemented(opcode); break;
        case 0x0000:
            switch (opcode) {
                default: notImplemented(opcode); break;
                case 0x00E0: clearScreen(); break;
                case 0x00EE: returnSubroutine(); break;
            }
            break;
        case 0x1000: jumpToAdress(); break;
        case 0x2000: executeSubroutine(); break;
        case 0x3000: /* todo */ break;
        case 0x4000: /* todo */ break;
        case 0x5000: /* todo */ break;
        case 0x6000: /* todo */ break;
        case 0x7000: /* todo */ break;
        case 0x8000:
            switch (opcode & 0x000F) {
                default: notImplemented(opcode); break;
                case 0x0000: /* todo */ break;
                case 0x0001: /* todo */ break;
                case 0x0002: /* todo */ break;
                case 0x0003: /* todo */ break;
                case 0x0004: /* todo */ break;
                case 0x0005: /* todo */ break;
                case 0x0006: /* todo */ break;
                case 0x0007: /* todo */ break;
                case 0x000E: /* todo */ break;
            }
            break;
        case 0x9000: /* todo */ break;
        case 0xA000: /* todo */ break;
        case 0xB000: /* todo */ break;
        case 0xC000: /* todo */ break;
        case 0xD000: /* todo */ break;
        case 0xE000: /* todo */ break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                default: notImplemented(opcode); break;
                case 0x0007: /* todo */ break;
                case 0x000A: /* todo */ break;
                case 0x0015: /* todo */ break;
                case 0x0018: /* todo */ break;
                case 0x001E: /* todo */ break;
                case 0x0029: /* todo */ break;
                case 0x0033: /* todo */ break;
                case 0x0055: /* todo */ break;
                case 0x0065: /* todo */ break;
            }
            break;
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

void Cpu::executeSubroutine()
{
    stack[sp] = pc;
    sp += 1;
    jumpToAdress();
}