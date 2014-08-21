#include "ad/Time.h"

namespace ad {

TimeClass Time;

TimeClass::TimeClass()
{
    frames = 0;
    ResetTime();
}


float TimeClass::deltaTime()
{
    return _deltaTime;
}

float TimeClass::fps()
{
    return _fps;
}
void TimeClass::Update()
{
    _deltaTime = clock.restart().asSeconds();

    if (fpsClock.getElapsedTime().asSeconds() < 1) frames++;
    else
    {
        _fps = frames;
        frames = 0;
        fpsClock.restart();
    }

    seconds += _deltaTime;
    if (seconds >= 60)
    {
        seconds -= 60;
        minutes++;
    }
    if (minutes >= 60)
    {
        minutes -= 60;
        hours++;
    }
}

} // namespace ad
