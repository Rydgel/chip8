#include <iostream>
#include <random>
#include <thread>
#include <fmt/format.h>
#include "Cpu.hpp"

static auto notImplemented(const uint16_t opcode)
{
    std::cout << "Error not implemented: " << fmt::format("{0:#x}", opcode) << std::endl;
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

std::ostream & operator<<(std::ostream & outputStream, const Cpu & c)
{
    outputStream
            << "Chip8" << std::endl
            << "draw flags: " << std::boolalpha << c.drawFlag << std::endl
            << "opcode: " << fmt::format("{0:#x}", c.opcode) << std::endl
            << "index: " << fmt::format("{0:#x}", c.index) << std::endl
            << "pc: " << fmt::format("{0:#x}", c.pc) << std::endl
            << "t_delay: " << fmt::format("{0:d}", c.timerDelay) << std::endl
            << "t_sound: " << fmt::format("{0:d}", c.timerSound) << std::endl
            << "r0: " << fmt::format("{0:#x}", c.registers[0]) << " "
            << "r1: " << fmt::format("{0:#x}", c.registers[1]) << " "
            << "r2: " << fmt::format("{0:#x}", c.registers[2]) << " "
            << "r3: " << fmt::format("{0:#x}", c.registers[3]) << " "
            << "r4: " << fmt::format("{0:#x}", c.registers[4]) << " "
            << "r5: " << fmt::format("{0:#x}", c.registers[5]) << " "
            << "r6: " << fmt::format("{0:#x}", c.registers[6]) << " "
            << "r7: " << fmt::format("{0:#x}", c.registers[7]) << " "
            << "r8: " << fmt::format("{0:#x}", c.registers[8]) << " "
            << "r9: " << fmt::format("{0:#x}", c.registers[9]) << " "
            << "r10: " << fmt::format("{0:#x}", c.registers[10]) << " "
            << "r11: " << fmt::format("{0:#x}", c.registers[11]) << " "
            << "r12: " << fmt::format("{0:#x}", c.registers[12]) << " "
            << "r13: " << fmt::format("{0:#x}", c.registers[13]) << " "
            << "r14: " << fmt::format("{0:#x}", c.registers[14]) << " "
            << "r15: " << fmt::format("{0:#x}", c.registers[15]) << std::endl
            << "sp: " << fmt::format("{0:#x}", c.sp) << std::endl;

    outputStream << "stack: ";
    for (auto && s : c.stack) {
        outputStream << fmt::format("{0:#x}", s) << " ";
    }
    outputStream << std::endl;
    outputStream << "graphics: " << std::endl;
    outputStream << "+----------------------------------------------------------------+" << std::endl;

    for (int i = 0; i < Constants::HEIGHT; i++) {
        for (int j = 0; j < Constants::WIDTH; j++) {
            if (c.pixels[i * Constants::WIDTH + j] == 0) {
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
                default: jumpToRoutine(); break;
                case 0x00E0: clearScreen(); break;
                case 0x00EE: returnSubroutine(); break;
            }
            break;
        case 0x1000: jumpToAdress(); break;
        case 0x2000: executeSubroutine(); break;
        case 0x3000: skipIfVXIsNN(); break;
        case 0x4000: skipIfVXIsNotNN(); break;
        case 0x5000: skipIfRegXIsRegY(); break;
        case 0x6000: setRegXToNN(); break;
        case 0x7000: addNNToRegX(); break;
        case 0x8000:
            switch (opcode & 0x000F) {
                default: notImplemented(opcode); break;
                case 0x0000: setRegXToRegY(); break;
                case 0x0001: setRegXToRegXOrRegY(); break;
                case 0x0002: setRegXToRegXAndRegY(); break;
                case 0x0003: setRegXToRegXXorRegY(); break;
                case 0x0004: addVyToVx(); break;
                case 0x0005: substractVyFromVx(); break;
                case 0x0006: shiftVyRightIntoVx(); break;
                case 0x0007: setVxToVyMinusVx(); break;
                case 0x000E: shiftVyLeftIntoVx(); break;
            }
            break;
        case 0x9000: skipIfVxDifferentVy(); break;
        case 0xA000: storeMemoryInIndex(); break;
        case 0xB000: jumpToNNN(); break;
        case 0xC000: setRandom(); break;
        case 0xD000: draw(); break;
        case 0xE000:
            switch (opcode & 0x00FF) {
                default: notImplemented(opcode); break;
                case 0x009E: skipIfPressed(); break;
                case 0x00A1: skipIfNotPressed(); break;
            }
            break;
        case 0xF000:
            switch (opcode & 0x00FF) {
                default: notImplemented(opcode); break;
                case 0x0007: storeCurrentDelayInVx(); break;
                case 0x000A: waitKeypress(); break;
                case 0x0015: setDelayTimer(); break;
                case 0x0018: setSoundTimer(); break;
                case 0x001E: setIndex(); break;
                case 0x0029: setIndexSprite(); break;
                case 0x0033: storeDecimalRegX(); break;
                case 0x0055: storeRegisters(); break;
                case 0x0065: fillRegisters(); break;
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

void Cpu::emulateCycle()
{
    fetchOpcode();
    executeOpcode();
    updateTimers();
}

void Cpu::jumpToRoutine()
{
    std::cout << "Error not implemented jumpToRoutine() " << std::endl;
    notImplemented(opcode);
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

void Cpu::skipIfVXIsNN()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto nn = static_cast<uint8_t>(opcode & 0x00FF);
    if (registers[x] == nn) {
        pc += 2;
    }
    pc += 2;
}

void Cpu::skipIfVXIsNotNN()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto nn = static_cast<uint8_t>(opcode & 0x00FF);
    if (registers[x] != nn) {
        pc += 2;
    }
    pc += 2;
}

void Cpu::skipIfRegXIsRegY()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;
    if (registers[x] == registers[y]) {
        pc += 2;
    }
    pc += 2;
}

void Cpu::setRegXToNN()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto nn = static_cast<uint8_t>(opcode & 0x00FF);
    registers[x] = nn;
    pc += 2;
}

void Cpu::addNNToRegX()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto nn = static_cast<uint8_t>(opcode & 0x00FF);
    registers[x] += nn;
    pc += 2;
}

void Cpu::setRegXToRegY()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;
    registers[x] = registers[y];
    pc += 2;
}

void Cpu::setRegXToRegXOrRegY()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;
    registers[x] |= registers[y];
    pc += 2;
}

void Cpu::setRegXToRegXAndRegY()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;
    registers[x] &= registers[y];
    pc += 2;
}

void Cpu::setRegXToRegXXorRegY()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;
    registers[x] ^= registers[y];
    pc += 2;
}

void Cpu::addVyToVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;

    if (registers[y] > 0xFF - registers[x]) {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[x] += registers[y];
    pc += 2;
}

void Cpu::substractVyFromVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;

    if (registers[y] > registers[x]) {
        registers[0xF] = 0;
    } else {
        registers[0xF] = 1;
    }

    registers[x] -= registers[y];
    pc += 2;
}

void Cpu::shiftVyRightIntoVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto lsb = static_cast<uint8_t>(registers[x] & 0x0001);
    registers[0xF] = lsb;
    registers[x] >>= 1;
    pc += 2;
}

void Cpu::setVxToVyMinusVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;

    if (registers[x] > registers[y]) {
        registers[0xF] = 0;
    } else {
        registers[0xF] = 1;
    }

    registers[x] = registers[y] - registers[x];
    pc += 2;
}

void Cpu::shiftVyLeftIntoVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto msb = static_cast<uint8_t>(registers[x] & 0x80) >> 7;
    registers[0xF] = msb;
    registers[x] <<= 1;
    pc += 2;
}

void Cpu::skipIfVxDifferentVy()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto y = (opcode & 0x00F0) >> 4;

    if (registers[x] != registers[y]) {
        pc += 2;
    }

    pc += 2;
}

void Cpu::storeMemoryInIndex()
{
    index = static_cast<uint16_t>(opcode & 0x0FFF);
    pc += 2;
}

void Cpu::jumpToNNN()
{
    const auto address = static_cast<uint16_t>(opcode & 0x0FFF);
    pc = registers[0] + address;
}

void Cpu::setRandom()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto nn = static_cast<uint8_t>(opcode & 0x00FF);

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<uint8_t> uniformDist(0, 255);
    const auto randNumber = uniformDist(e1);

    registers[x] = nn & randNumber;

    pc += 2;
}

void Cpu::draw()
{
    const auto x = registers[(opcode & 0x0F00) >> 8];
    const auto y = registers[(opcode & 0x00F0) >> 4];
    const auto height = opcode & 0x000F;

    registers[0xF] = 0;

    for (int yy = 0; yy < height; yy ++) {
        auto pixelRow = memory.storage[index + yy];
        for (int xx = 0; xx < 8; xx ++) {
            if ((pixelRow & 0x80) != 0) {
                auto screenY = (y + yy) % HEIGHT;
                auto screenX = (x + xx) % WIDTH;
                auto address = (screenY * WIDTH) + screenX;
                if (pixels[address] == 1) {
                    registers[0xF] = 1;
                }
                pixels[address] ^= 1;
            }
            pixelRow <<= 1;
        }
    }

    drawFlag = true;
    pc += 2;
}

void Cpu::skipIfPressed()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto value = registers[x];

    if (key[value] != 0) {
        pc += 2;
    }

    pc += 2;
}

void Cpu::skipIfNotPressed()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto value = registers[x];

    if (key[value] == 0) {
        pc += 2;
    }

    pc += 2;
}

void Cpu::storeCurrentDelayInVx()
{
    const auto x = (opcode & 0x0F00) >> 8;
    registers[x] = timerDelay;
    pc += 2;
}

void Cpu::waitKeypress()
{
    using namespace std::chrono_literals;
    const auto x = (opcode & 0x0F00) >> 8;
    const auto oldPc = pc;

    std::vector<uint8_t> range(0xA);
    std::iota(std::begin(range), std::end(range), 0);

    for (auto && k : range) {
        if (key[k] != 0) {
            registers[x] = k;
            pc += 2;
            break;
        }
    }

    if (pc == oldPc) {
        // prevent bursting cpu
        std::this_thread::sleep_for(10ms);
    }
}

void Cpu::setDelayTimer()
{
    const auto x = (opcode & 0x0F00) >> 8;
    timerDelay = registers[x];
    pc += 2;
}

void Cpu::setSoundTimer()
{
    const auto x = (opcode & 0x0F00) >> 8;
    timerSound = registers[x];
    pc += 2;
}

void Cpu::setIndex()
{
    const auto x = (opcode & 0x0F00) >> 8;
    index += registers[x];
    pc += 2;
}

void Cpu::setIndexSprite()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto address = registers[x];
    index = static_cast<uint16_t>(5 * address);
    pc += 2;
}

void Cpu::storeDecimalRegX()
{
    const auto x = (opcode & 0x0F00) >> 8;
    const auto value = registers[x];
    memory.storage[index] = static_cast<uint8_t>(value / 100);
    memory.storage[index + 1] = static_cast<uint8_t>((value / 10) % 10);
    memory.storage[index + 2] = static_cast<uint8_t>((value % 100) % 10);
    pc += 2;
}

void Cpu::storeRegisters()
{
    const auto x = (opcode & 0x0F00) >> 8;

    for (int i = 0; i < x + 1; i ++) {
        memory.storage[index + i] = registers[i];
    }

    pc += 2;
}

void Cpu::fillRegisters()
{
    const auto x = (opcode & 0x0F00) >> 8;

    for (int i = 0; i < x + 1; i ++) {
        registers[i] = memory.storage[index + i];
    }

    pc += 2;
}
