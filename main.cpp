#include <iostream>
#include "ad/Game.h"

int main()
{
     // initialize Game class
    ad::GameClass* game = &ad::Game;
    if (game == NULL)
    {
        std::cout << "Problem initializing ad::Game :c\n";
        return 1;
    }

    // program main loop
    bool done = false;
    while (!done)
    {
        // update Game
        if (game->Update() == AD_QUITCODE)
        {
            // Received quit code
            done = true;
        }
    } // end main loop

    // all is well ;)
    std::cout << "Exited cleanly\n";
    return 0;
}
