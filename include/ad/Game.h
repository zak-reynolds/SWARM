#ifndef GAME_H
#define GAME_H

#include "ad/SceneManager.h"
#include "ad/I_EventManager.h"
#include "ad/I_GraphicsManager.h"
#include "ad/I_AudioManager.h"
#include "ad/SFML/SFML_Helper.h"
#include "ad/Math.h"
#include "ad/Time.h"

namespace ad
{

class GameClass
{
    public:
        /** Default constructor */
        GameClass();
        /** Default destructor */
        virtual ~GameClass();
        /** Update function */
        int Update();
        ad::SceneManager* SceneM() { return sceneManager; };
        ad::Graphics::I_GraphicsManager* GraphicsM() { return graphicsManager; };
        ad::Event::I_EventManager* EventM() { return eventManager; };
        ad::Sound::I_AudioManager* AudioM() { return soundManager; };
        SFML_Helper* GetSFML_Helper() { return helper; };
        gmtl::Vec2i GetResolution() { return resolution; }
        void SkipRender() { skipRender = true; }

        double Score;
        bool WonGame;
    protected:
    private:
        ad::SceneManager* sceneManager;
        ad::Graphics::I_GraphicsManager* graphicsManager;
        ad::Event::I_EventManager* eventManager;
        ad::Sound::I_AudioManager* soundManager;
        SFML_Helper *helper;
        gmtl::Vec2i resolution;
        bool skipRender;
};

extern ad::GameClass Game;

}
#endif // GAME_H
