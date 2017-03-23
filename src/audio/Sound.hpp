#ifndef CHIP8_SOUND_HPP
#define CHIP8_SOUND_HPP

#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#endif
#include <iostream>
#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <array>


struct Sound
{
    Sound();
    ~Sound();

    void playBeep();
    void stopSound();

private:

    ALCdevice * device_ = nullptr;
    ALCcontext * context_ = nullptr;
    ALuint source_ = 0;
    ALuint buffer_ = 0;

    void createBuffer();
    void checkErrors();
};


#endif //CHIP8_SOUND_HPP
