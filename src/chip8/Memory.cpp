#include "Memory.hpp"

Memory::Memory()
{
    clearMemory();
    initFontSet();
}

void Memory::clearMemory()
{
    storage_.fill(0);
}

void Memory::initFontSet()
{
    auto index = 0;
    for (auto &e : Constants::FONT_SET) {
        storage_[index] = static_cast<uint8_t>(e);
        index ++;
    }
}

void Memory::loadBinary(const std::vector<uint8_t> binary)
{
    auto index = 0;
    for (auto &e : binary) {
        storage_[index + 512] = e;
        index ++;
    }
}

const uint16_t Memory::fetchOpcode(const uint16_t pc)
{
    return storage_[pc] << 8 | storage_[pc + 1];
}
