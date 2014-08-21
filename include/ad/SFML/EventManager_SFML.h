#ifndef EVENTMANAGER_SFML_H
#define EVENTMANAGER_SFML_H

#include "ad/I_EventManager.h"
#include <SFML/Graphics.hpp>
#include <list>

namespace ad {
namespace Event {

class EventManager_SFML : public I_EventManager
{
    public:
        /** Default constructor */
        EventManager_SFML();
        /** Default destructor */
        ~EventManager_SFML();
        void Initialize();
        int Update();
        void Destroy();

        bool GetKey(ad::Event::Key KeyCode);
        bool GetKeyPress(ad::Event::Key KeyCode);
        bool GetKeyRelease(ad::Event::Key KeyCode);
        float GetMouseWorldX();
        float GetMouseWorldY();
        int GetMouseX();
        int GetMouseY();

        void CreateEvent(ad::Event::EventType Type);

        void RegisterListener(void (*callback)());
    protected:
    private:
        sf::RenderWindow *window;
        std::list<ad::Event::Key> pressedKeys;
        std::list<ad::Event::Key> releasedKeys;
        std::list<ad::Event::Key> heldKeys;
        bool KeyListHasKey(std::list<ad::Event::Key>*, ad::Event::Key Key);
        std::vector<ad::Event::EventType> events;
};

}
}
#endif // EVENTMANAGER_SFML_H
