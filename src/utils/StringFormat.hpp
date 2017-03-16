#ifndef CHIP8_STRINGFORMAT_HPP
#define CHIP8_STRINGFORMAT_HPP

#include <iostream>
#include <memory>
#include <string>
#include <cstdio>

template <typename T>
T processArg(T value) noexcept
{
    return value;
}

template <typename T>
T const * processArg(std::basic_string<T> const & value) noexcept
{
    return value.c_str();
}

template<typename ... Args>
std::string stringFormat(const std::string& format, Args const & ... args)
{
    const auto fmt = format.c_str();
    const size_t size = static_cast<size_t>(std::snprintf(nullptr, 0, fmt, processArg(args) ...) + 1);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, fmt, processArg(args) ...);
    return std::string(buf.get(), buf.get() + size - 1);
}

#endif //CHIP8_STRINGFORMAT_HPP
