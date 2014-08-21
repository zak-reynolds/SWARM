#include "ad/SFML/EventManager_SFML.h"
#include "ad/Game.h"
#include <SFML/Window.hpp>
#include <iostream>

namespace ad {
namespace Event {

EventManager_SFML::EventManager_SFML()
{
    window = ad::Game.GetSFML_Helper()->GetmainWindow();
}

EventManager_SFML::~EventManager_SFML()
{
    //dtor
}

void EventManager_SFML::Initialize()
{

}

bool EventManager_SFML::KeyListHasKey(std::list<ad::Event::Key>* keyList, ad::Event::Key Key)
{
    for (auto it = keyList->begin(); it != keyList->end(); ++it)
    {
        if (*it == Key)
        {
            return true;
        }
    }
    return false;
}

int EventManager_SFML::Update()
{
    // clear key states
    pressedKeys.clear();
    releasedKeys.clear();

    // message processing loop
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            return AD_QUITCODE;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if(!KeyListHasKey(&heldKeys, static_cast<ad::Event::Key>(event.key.code)))
            {
                pressedKeys.push_back(static_cast<ad::Event::Key>(event.key.code));
                heldKeys.push_back(static_cast<ad::Event::Key>(event.key.code));
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (Game.SceneM()->GetcurrentScene()->GetFileName() == "test-scene.xml")
                {
                    Game.SceneM()->NextScene("title.xml");
                    Game.WonGame = false;
                }
                else
                {
                    window->close();
                    return AD_QUITCODE;
                }
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            releasedKeys.push_back(static_cast<ad::Event::Key>(event.key.code));
            heldKeys.remove(static_cast<ad::Event::Key>(event.key.code));
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            // Hard code mouse presses because of difference between sfml and ad enums
            if(event.mouseButton.button == sf::Mouse::Right && !KeyListHasKey(&heldKeys, ad::Event::MouseRight))
            {
                pressedKeys.push_back(ad::Event::MouseRight);
                heldKeys.push_back(ad::Event::MouseRight);
            }
            else if(event.mouseButton.button == sf::Mouse::Left && !KeyListHasKey(&heldKeys, ad::Event::MouseLeft))
            {
                pressedKeys.push_back(ad::Event::MouseLeft);
                heldKeys.push_back(ad::Event::MouseLeft);
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            // Hard code mouse presses because of difference between sfml and ad enums
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                releasedKeys.push_back(ad::Event::MouseLeft);
                heldKeys.remove(ad::Event::MouseLeft);
            }
            else if(event.mouseButton.button == sf::Mouse::Right)
            {
                releasedKeys.push_back(ad::Event::MouseRight);
                heldKeys.remove(ad::Event::MouseRight);
            }
        }
    }

    while (!events.empty())
    {
        ad::Event::EventType e = events.back();

        if (e == ad::Event::EventType::WindowClose)
        {
            window->close();
            return AD_QUITCODE;
        }

        events.pop_back();
    }
    return AD_NORMALCODE;
}
void EventManager_SFML::Destroy()
{

}

bool EventManager_SFML::GetKey(ad::Event::Key KeyCode)
{
    return KeyListHasKey(&heldKeys, KeyCode);
}
bool EventManager_SFML::GetKeyPress(ad::Event::Key KeyCode)
{
    return KeyListHasKey(&pressedKeys, KeyCode);
}
bool EventManager_SFML::GetKeyRelease(ad::Event::Key KeyCode)
{
    return KeyListHasKey(&releasedKeys, KeyCode);
}
float EventManager_SFML::GetMouseWorldX()
{
    return ((float)GetMouseX() - .5 * (float)(window->getSize().x)) + Game.GraphicsM()->CameraX();
}
float EventManager_SFML::GetMouseWorldY()
{
    return ((float)GetMouseY() - .5 * (float)(window->getSize().y)) + Game.GraphicsM()->CameraY();
}
int EventManager_SFML::GetMouseX()
{
    return sf::Mouse::getPosition(*window).x;
}
int EventManager_SFML::GetMouseY()
{
    return sf::Mouse::getPosition(*window).y;
}

void EventManager_SFML::CreateEvent(ad::Event::EventType Type)
{
    events.push_back(Type);
}

void EventManager_SFML::RegisterListener(void (*callback)())
{

}

}
}

