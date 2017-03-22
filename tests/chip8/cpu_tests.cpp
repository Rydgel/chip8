#include "gtest/gtest.h"
#include "chip8/Memory.hpp"
#include "chip8/Cpu.hpp"

TEST(cpu, op_00e0) {
    Memory memory;
    memory.loadBinary({ 0x00, 0xE0 });
    Cpu cpu { memory };
    cpu.pixels[1] = 1;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.pixels[1], 0);
}

TEST(cpu, op_00ee) {
    Memory memory;
    memory.loadBinary({ 0x00, 0xEE });
    Cpu cpu { memory };
    cpu.stack[0] = 0x42;
    cpu.sp = 1;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 0x44);
    EXPECT_EQ(cpu.sp, 0);
}

TEST(cpu, op_1nnn) {
    Memory memory;
    memory.loadBinary({ 0x16, 0x66 });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 0x666);
}

TEST(cpu, op_2nnn) {
    Memory memory;
    memory.loadBinary({ 0x26, 0x66 });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 0x666);
    EXPECT_EQ(cpu.stack[0], 512);
    EXPECT_EQ(cpu.sp, 1);
}

TEST(cpu, op_3nnn) {
    Memory memory;
    memory.loadBinary({ 0x31, 0x66, 0x31, 0x67 });
    Cpu cpu { memory };
    cpu.registers[1] = 0x67;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_4nnn) {
    Memory memory;
    memory.loadBinary({ 0x41, 0x66, 0x41, 0x67 });
    Cpu cpu { memory };
    cpu.registers[1] = 0x66;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_5xy0) {
    Memory memory;
    memory.loadBinary({ 0x51, 0x20, 0x51, 0x30 });
    Cpu cpu { memory };
    cpu.registers[1] = 0x66;
    cpu.registers[2] = 0x22;
    cpu.registers[3] = 0x66;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_6xnn) {
    Memory memory;
    memory.loadBinary({ 0x6A, 0x2F });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.registers[0xA], 0);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0x2F);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_7xnn) {
    Memory memory;
    memory.loadBinary({ 0x7A, 0x2F });
    Cpu cpu { memory };

    cpu.registers[0xA] = 0xB;

    EXPECT_EQ(cpu.registers[0xA], 0xB);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0x2F + 0xB);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_8xy0) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0x20 });
    Cpu cpu { memory };
    cpu.registers[0xA] = 0xB;
    cpu.registers[0x2] = 0xC;

    EXPECT_EQ(cpu.registers[0xA], 0xB);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0xC);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_8xy1) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0x21 });
    Cpu cpu { memory };

    cpu.registers[0xA] = 0xB;
    cpu.registers[0x2] = 0xC;
    EXPECT_EQ(cpu.registers[0xA], 0xB);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0xB | 0xC);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_8xy2) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0x22 });
    Cpu cpu { memory };

    cpu.registers[0xA] = 0xB;
    cpu.registers[0x2] = 0xC;
    EXPECT_EQ(cpu.registers[0xA], 0xB);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0xB & 0xC);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_8xy3) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0x23 });
    Cpu cpu { memory };

    cpu.registers[0xA] = 0xB;
    cpu.registers[0x2] = 0xC;
    EXPECT_EQ(cpu.registers[0xA], 0xB);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.registers[0xA], 0xB ^ 0xC);
    EXPECT_EQ(cpu.registers[0x2], 0xC);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_8xy4) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0xB4, 0x8B, 0xC4 });
    Cpu cpu { memory };

    cpu.registers[0xA] = 0x00;
    cpu.registers[0xB] = 0xFF;
    cpu.registers[0xC] = 0x01;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0xA], 0xFF);
    EXPECT_EQ(cpu.registers[0xB], 0xFF);
    EXPECT_EQ(cpu.registers[0xF], 0x00);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 516);
    EXPECT_EQ(cpu.registers[0xB], 0x00);
    EXPECT_EQ(cpu.registers[0xC], 0x01);
    EXPECT_EQ(cpu.registers[0xF], 0x01);
}

TEST(cpu, op_8xy5) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0xB5, 0x8A, 0xB5 });
    Cpu cpu { memory };
    cpu.registers[0xA] = 0x01;
    cpu.registers[0xB] = 0x02;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0xA], 0xFF);
    EXPECT_EQ(cpu.registers[0xB], 0x02);
    EXPECT_EQ(cpu.registers[0xF], 0x00);

    cpu.registers[0xA] = 0x02;
    cpu.registers[0xB] = 0x01;

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 516);
    EXPECT_EQ(cpu.registers[0xA], 0x01);
    EXPECT_EQ(cpu.registers[0xB], 0x01);
    EXPECT_EQ(cpu.registers[0xF], 0x01);
}

TEST(cpu, op_8x06) {
    Memory memory;
    memory.loadBinary({ 0x81, 0x06 });
    Cpu cpu { memory };
    cpu.registers[0x1] = 0b011;

    EXPECT_EQ(cpu.pc, 512);
    EXPECT_EQ(cpu.registers[0xF], 0);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0x1], 0b01);
    EXPECT_EQ(cpu.registers[0xF], 0x1);
}

TEST(cpu, op_8xy7) {
    Memory memory;
    memory.loadBinary({ 0x8A, 0xB7, 0x8A, 0xB7 });
    Cpu cpu { memory };
    cpu.registers[0xA] = 0x01;
    cpu.registers[0xB] = 0x02;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0xA], 0x01);
    EXPECT_EQ(cpu.registers[0xB], 0x02);
    EXPECT_EQ(cpu.registers[0xF], 0x01);

    cpu.registers[0xA] = 0x02;
    cpu.registers[0xB] = 0x01;

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 516);
    EXPECT_EQ(cpu.registers[0xA], 0xFF);
    EXPECT_EQ(cpu.registers[0xB], 0x01);
    EXPECT_EQ(cpu.registers[0xF], 0x0);
}

TEST(cpu, op_8x0e) {
    Memory memory;
    memory.loadBinary({ 0x81, 0x0E });
    Cpu cpu { memory };
    cpu.registers[0x1] = 0x81;

    EXPECT_EQ(cpu.pc, 512);
    EXPECT_EQ(cpu.registers[0xF], 0);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0x1], static_cast<uint8_t>(0x81 << 1));
    EXPECT_EQ(cpu.registers[0xF], 0x1);
}

TEST(cpu, op_9xy0) {
    Memory memory;
    memory.loadBinary({ 0x91, 0x20, 0x91, 0x30 });
    Cpu cpu { memory };
    cpu.registers[0x1] = 0x81;
    cpu.registers[0x2] = 0x81;
    cpu.registers[0x3] = 0x82;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_annn) {
    Memory memory;
    memory.loadBinary({ 0xA6, 0x66 });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.index, 0);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.index, 0x666);
    EXPECT_EQ(cpu.pc, 514);
}

TEST(cpu, op_bnnn) {
    Memory memory;
    memory.loadBinary({ 0xB6, 0x66 });
    Cpu cpu { memory };
    cpu.registers[0] = 0x5;

    EXPECT_EQ(cpu.index, 0);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.index, 0);
    EXPECT_EQ(cpu.pc, 0x666 + 0x5);
}

TEST(cpu, op_ex9e) {
    Memory memory;
    memory.loadBinary({ 0xE1, 0x9E, 0xE1, 0x9E });
    Cpu cpu { memory };
    cpu.registers[1] = 1;
    cpu.key[1] = 0;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    cpu.key[1] = 1;

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_exa1) {
    Memory memory;
    memory.loadBinary({ 0xE1, 0xA1, 0xE1, 0xA1 });
    Cpu cpu { memory };
    cpu.registers[1] = 1;
    cpu.key[1] = 1;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);
    EXPECT_EQ(cpu.pc, 514);
    cpu.key[1] = 0;

    cpu.emulateCycle(1.0f);
    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_fx07) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x07 });
    Cpu cpu { memory };
    cpu.timerDelay = 10;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[1], 10);
}

TEST(cpu, op_fx0a) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x0A });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.registers[1], 0);
    EXPECT_EQ(cpu.key[1], 0);
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 512);
    cpu.key[1] = 1;

    cpu.emulateCycle(1.0f);
    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[1], 1);
}

TEST(cpu, op_fx15) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x15 });
    Cpu cpu { memory };
    cpu.registers[1] = 10;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.timerDelay, 9);
}

TEST(cpu, op_fx18) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x18 });
    Cpu cpu { memory };

    cpu.registers[1] = 10;
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.timerSound, 9);
}

TEST(cpu, op_fx1e) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x1E });
    Cpu cpu { memory };

    cpu.registers[1] = 10;
    const auto initIndex = cpu.index;
    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.index, initIndex + cpu.registers[1]);
    EXPECT_EQ(cpu.registers[1], 10);
}

TEST(cpu, op_fx29) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x29 });
    Cpu cpu { memory };
    cpu.registers[1] = 0xA;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.index, cpu.registers[1] * 5);
    EXPECT_EQ(cpu.registers[1], 0xA);
}

TEST(cpu, op_fx55) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x55 });
    Cpu cpu { memory };

    cpu.index = 10;
    cpu.registers[0] = 0xAB;
    cpu.registers[1] = 0xCD;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.memory.storage[10], 0xAB);
    EXPECT_EQ(cpu.memory.storage[11], 0xCD);
}

TEST(cpu, op_fx65) {
    Memory memory;
    memory.loadBinary({ 0xF1, 0x65 });
    Cpu cpu { memory };

    cpu.memory.storage[10] = 0xAB;
    cpu.memory.storage[11] = 0xCD;
    cpu.index = 10;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle(1.0f);

    EXPECT_EQ(cpu.pc, 514);
    EXPECT_EQ(cpu.registers[0], 0xAB);
    EXPECT_EQ(cpu.registers[1], 0xCD);
}