#include "Timer.hpp"

void Timer::init()
{
    lastLoopTime_ = getTime();
    timeCount_ = 0.0;
    fps_ = 0;
    fpsCount_ = 0;
    ups_ = 0;
    upsCount_ = 0;
}

const double Timer::getTime()
{
    const auto duration = Clock::now().time_since_epoch();
    const auto getMs = std::chrono::duration_cast<MilliSeconds>(duration).count();
    return getMs / 1000.0;
}

const float Timer::getDelta()
{
    const double time = getTime();
    const float delta = static_cast<float>(time - lastLoopTime_);
    lastLoopTime_ = time;
    timeCount_ += delta;
    return delta;
}

void Timer::updateFPS()
{
    fpsCount_ ++;
}

void Timer::updateUPS()
{
    upsCount_ ++;
}

void Timer::update()
{
    if (timeCount_ > 1.0) {
        fps_ = fpsCount_;
        fpsCount_ = 0;

        ups_ = upsCount_;
        upsCount_ = 0;

        timeCount_ -= 1.0;
    }
}

const int Timer::getFPS()
{
    return fps_ > 0 ? fps_ : fpsCount_;
}

const int Timer::getUPS()
{
    return ups_ > 0 ? ups_ : upsCount_;
}