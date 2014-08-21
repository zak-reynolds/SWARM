#include "ad/SFML/SFML_Helper.h"
#include <vector>

SFML_Helper::SFML_Helper()
{
    // Best mode
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    mainWindow = new sf::RenderWindow(sf::VideoMode(modes[0].width, modes[0].height, modes[0].bitsPerPixel), "/// SWARM");
    mainWindow->setMouseCursorVisible(false);
}
