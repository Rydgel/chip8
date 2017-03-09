#include "Chip8.hpp"

void Chip8::emulateCycle()
{
    // fetch and execute opcode inside cpu_
    cpu_.fetchOpcode();
    cpu_.executeOpcode();
    // update timers and sounds flag
    cpu_.updateTimers();
}