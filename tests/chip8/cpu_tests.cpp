#include "gtest/gtest.h"
#include "chip8/Memory.hpp"
#include "chip8/Cpu.hpp"

TEST(cpu, op_00e0) {
    Memory memory;
    memory.loadBinary({ 0x00, 0xE0 });
    Cpu cpu { memory };
    cpu.pixels[1] = 1;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle();

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

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 0x44);
    EXPECT_EQ(cpu.sp, 0);
}

TEST(cpu, op_1nnn) {
    Memory memory;
    memory.loadBinary({ 0x16, 0x66 });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 0x666);
}

TEST(cpu, op_2nnn) {
    Memory memory;
    memory.loadBinary({ 0x26, 0x66 });
    Cpu cpu { memory };

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle();

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

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 518);
}

TEST(cpu, op_4nnn) {
    Memory memory;
    memory.loadBinary({ 0x41, 0x66, 0x41, 0x67 });
    Cpu cpu { memory };
    cpu.registers[1] = 0x66;

    EXPECT_EQ(cpu.pc, 512);

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 514);

    cpu.emulateCycle();

    EXPECT_EQ(cpu.pc, 518);
}