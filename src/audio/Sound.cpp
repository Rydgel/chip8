#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#endif
#include <iostream>
#include "Sound.hpp"

Sound::Sound()
{
    // todo remove test
    ALCdevice *device = alcOpenDevice(nullptr);
    if (!device) {
        // error not sound devices
    }

    alcCloseDevice(device);
}

void Sound::playBeep()
{
    // todo
    std::cout << "bip" << std::endl;
}
