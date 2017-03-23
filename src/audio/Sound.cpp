#include "Sound.hpp"

Sound::Sound()
{
    device_ = alcOpenDevice(nullptr);
    context_ = alcCreateContext(device_, nullptr);
    alcMakeContextCurrent(context_);

    alGenSources(1, &source_);
    alGenBuffers(1, &buffer_);

    createBuffer();

    alSourcef(source_, AL_PITCH, 1);
    alSourcef(source_, AL_GAIN, 1);
    alSource3f(source_, AL_POSITION, 0, 0, 0);
    alSource3f(source_, AL_VELOCITY, 0, 0, 0);
    alSourcei(source_, AL_LOOPING, AL_FALSE);
    alSourcei(source_, AL_BUFFER, buffer_);

    checkErrors();
}

Sound::~Sound()
{
    alDeleteSources(1, &source_);
    alDeleteBuffers(1, &buffer_);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context_);
    alcCloseDevice(device_);

    checkErrors();
}

void Sound::playBeep()
{
    ALint state = 0;
    alGetSourcei(source_, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING) {
        alSourcePlay(source_);
    }

    checkErrors();
}

void Sound::stopSound()
{
    ALint state = 0;
    alGetSourcei(source_, AL_SOURCE_STATE, &state);
    if (state == AL_PLAYING) {
        alSourceStop(source_);
    }

    checkErrors();
}

void Sound::createBuffer()
{
    constexpr auto freq = 400.0f;
    constexpr auto seconds = 1;
    constexpr auto sampleRate = 44100;
    constexpr auto bufSize = seconds * sampleRate;
    std::array<short, bufSize> samples;

    for (int i = 0; i < bufSize; i ++) {
        auto wave = static_cast<short>(32760 * sin((2.0f * M_PI * freq) / sampleRate * i));
        samples[i] = (short) (wave > 0 ? 32760 : -32760);
    }

    alBufferData(buffer_, AL_FORMAT_MONO16, samples.data(), bufSize, sampleRate);
}

void Sound::checkErrors()
{
    ALenum err = alGetError();

    for (; err != AL_NO_ERROR; err = alGetError()) {
        std::cerr << "AL Error ";

        switch (err) {
            default: break;
            case AL_INVALID_NAME: std::cerr << "invalid name" << std::endl; break;
            case AL_INVALID_ENUM: std::cerr << "invalid enum" << std::endl; break;
            case AL_INVALID_VALUE: std::cerr << "invalid value" << std::endl; break;
            case AL_INVALID_OPERATION: std::cerr << "invalid operation" << std::endl; break;
            case AL_OUT_OF_MEMORY: std::cerr << "out of memory" << std::endl; break;
        }
    }
}
