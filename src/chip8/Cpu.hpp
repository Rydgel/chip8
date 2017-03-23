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
    friend std::ostream & operator <<(std::ostream & outputStream, const Cpu & c);

    void emulateCycle(const float dt);
private:

    float globalCyclesDelta_ = 0;
    float globalTimersDelta_ = 0;

    void fetchOpcode();
    void executeOpcode();
    void updateTimers(const float dt);

    /// 0xNNN
    /// Jump to a machine code routine at nnn.
    /// This instruction is only used on the old computers on which Chip-8
    /// was originally implemented. It is ignored by modern interpreters.
    /// This will not be implemented.
    void jumpToRoutine();
    /// 0x00E0
    /// Clear the screen
    void clearScreen();
    /// 0x00EE
    /// Return from a subroutine
    void returnSubroutine();
    /// 0x1NNN
    /// Jump to address NNN
    void jumpToAdress();
    /// 0x2NNN
    /// Execute subroutine starting at address NNN
    void executeSubroutine();
    /// 0x3XNN
    /// Skip the following instruction
    /// if the value of register VX equals NN
    void skipIfVXIsNN();
    /// 0x4XNN
    /// Skip the following instruction
    /// if the value of register VX is not equal to NN
    void skipIfVXIsNotNN();
    /// 0x5XY0
    /// Skip the following instruction
    /// if the value of register VX is equal to the value of register VY
    void skipIfRegXIsRegY();
    /// 0x6XNN Store number NN in register VX
    void setRegXToNN();
    /// 0x7XNN
    /// Add the value NN to register VX
    void addNNToRegX();
    /// 0x8XY0
    /// Store the value of register VY in register VX
    void setRegXToRegY();
    /// 0x8XY1
    /// Set VX to VX OR VY
    void setRegXToRegXOrRegY();
    /// 0x8XY2
    /// Set VX to VX AND VY
    void setRegXToRegXAndRegY();
    /// 0x8XY3
    /// Set VX to VX XOR VY
    void setRegXToRegXXorRegY();
    /// 0x8XY4
    /// Add the value of register VY to register VX
    /// Set VF to 01 if a carry occurs
    /// Set VF to 00 if a carry does not occur
    void addVyToVx();
    /// 0x8XY5
    /// Subtract the value of register VY from register VX
    /// Set VF to 00 if a borrow occurs
    /// Set VF to 01 if a borrow does not occur
    void substractVyFromVx();
    /// 0x8XY6
    /// Store the value of register VY shifted right one bit in register VX
    /// Set register VF to the least significant bit prior to the shift
    void shiftVyRightIntoVx();
    /// 0x8XY7
    /// Set register VX to the value of VY minus VX
    /// Set VF to 00 if a borrow occurs
    /// Set VF to 01 if a borrow does not occur
    void setVxToVyMinusVx();
    /// 0x8XYE
    /// Store the value of register VY shifted left one bit in register VX
    /// Set register VF to the most significant bit prior to the shift
    void shiftVyLeftIntoVx();
    /// 0x9XY0
    /// Skip the following instruction if the value of register VX
    /// is not equal to the value of register VY
    void skipIfVxDifferentVy();
    /// 0xANNN
    /// Store memory address NNN in register I
    void storeMemoryInIndex();
    /// 0xBNNN
    /// Jump to address NNN + V0
    void jumpToNNN();
    /// 0xCXNN
    /// Set VX to a random number with a mask of NN
    void setRandom();
    /// 0xDXYN
    /// Draw a sprite at position VX, VY with N bytes of sprite data starting
    /// at the address stored in I
    /// Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
    void draw();
    /// 0xEX9E
    /// Skip the following instruction if the key corresponding
    /// to the hex value currently stored in register VX is pressed
    void skipIfPressed();
    /// 0xEXA1
    /// Skip the following instruction if the key corresponding
    /// to the hex value currently stored in register VX is not pressed
    void skipIfNotPressed();
    /// 0xFX07
    /// Store the current value of the delay timer in register VX
    void storeCurrentDelayInVx();
    /// 0xFX0A
    /// Wait for a keypress and store the result in register VX
    void waitKeypress();
    /// 0xFX15
    /// Set the delay timer to the value of register VX
    void setDelayTimer();
    /// 0xFX18
    /// Set the sound timer to the value of register VX
    void setSoundTimer();
    /// 0xFX1E
    /// Add the value stored in register VX to register I
    void setIndex();
    /// OxFX29
    /// Set I to the memory address of the sprite data corresponding
    /// to the hexadecimal digit stored in register VX
    void setIndexSprite();
    /// 0xFX33
    /// Store the binary-coded decimal equivalent of the value
    /// stored in register VX at addresses I, I+1, and I+2
    void storeDecimalRegX();
    /// 0xFX55
    /// Store the values of registers V0 to VX inclusive in memory starting at address I
    /// I is set to I + X + 1 after operation
    void storeRegisters();
    /// 0xFX65
    /// Fill registers V0 to VX inclusive with the values stored in memory starting at address I
    /// I is set to I + X + 1 after operation
    void fillRegisters();
};


#endif //CHIP8_CPU_HPP
