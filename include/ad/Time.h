#ifndef AD_TIME_H
#define AD_TIME_H

#include "SFML/System.hpp"

namespace ad {

class TimeClass
{
    public:
        /** Default constructor */
        TimeClass();
        //! Returns time since last step (in seconds)
        float deltaTime();
        //! Returns current FPS
        float fps();
        void Update();

        int GetSeconds() { return (int)seconds; }
        int GetMinutes() { return minutes; }
        int GetHours() { return hours; }

        void ResetTime() { seconds = 0; minutes = 0; hours = 0; }
    protected:
    private:
        sf::Clock clock;
        sf::Clock fpsClock;
        float _deltaTime;
        int frames;
        float _fps;

        float seconds;
        int minutes;
        int hours;
};

extern TimeClass Time;

} // namespace ad

#endif // AD_TIME_H
