#ifndef CHIP8_TIMER_HPP
#define CHIP8_TIMER_HPP

#include <chrono>


struct Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using MilliSeconds = std::chrono::milliseconds;

    void init();
    const double getTime();
    const float getDelta();
    void updateFPS();
    void updateUPS();
    void update();
    const int getFPS();
    const int getUPS();

private:

    double lastLoopTime_;
    float timeCount_;
    int fps_;
    int fpsCount_;
    int ups_;
    int upsCount_;
};


#endif //CHIP8_TIMER_HPP
