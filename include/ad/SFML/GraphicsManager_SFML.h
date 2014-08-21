#ifndef AXOLDRIVE_GRAPHICS_GRAPHICSMANAGER_SFML_H
#define AXOLDRIVE_GRAPHICS_GRAPHICSMANAGER_SFML_H

#include "ad/I_GraphicsManager.h"

#include "ad/Components/Sprite.h"
#include "ad/Components/Text.h"

#include "SFML/Graphics.hpp"

namespace ad {
namespace Graphics {

class GraphicsManager_SFML : public I_GraphicsManager
{
    public:
        /** Default constructor */
        GraphicsManager_SFML();
        /** Default destructor */
        ~GraphicsManager_SFML();

        int Initialize();
        void Update();
        void Destroy();

        int DrawTexture(int x, int y, std::string);
        void ClearScreen();
        void DrawRectangle(int x, int y, int w, int h, int r, int g, int b, int a);
        void DrawCircle(int x, int y, int rad, int r, int g, int b, int a);

        int LoadTexture(std::string);
        int LoadTexturesAsync(ad::VectorS* Textures);
        int UnloadTexture(std::string);
        int LoadFont(std::string);
        int UnloadFont(std::string);

        void SetCurrentRootGameobject(ad::Gob* root);

        void AddSprite(ad::Gob* Gob);
        void RemoveSprite(std::string Gob);
        void AddText(ad::Gob* Gob);
        void RemoveText(std::string Gob);

        float CameraX();
        float CameraY();
        gmtl::Vec2f CameraPosition();

        gmtl::Vec2f ScreenSize();
    protected:
    private:
        std::unordered_map<std::string, sf::Texture> loadedTextures;
        std::unordered_map<std::string, sf::Font> loadedFonts;
        // <Gameobject name, pointer to SFML Sprite>
        std::map<std::string, sf::Sprite*> currentSFSprites;
        std::map<std::string, sf::Text*> currentSFTexts;
        std::unordered_map<std::string, ad::Comps::Sprite*> currentSprites;
        std::unordered_map<std::string, ad::Comps::Text*> currentTexts;
        std::unordered_map<std::string, ad::Comps::Transform*> currentDrawableTransforms;
        ad::Comps::Transform* cameraTransform;
        sf::RenderWindow* window;
        void CheckForSprite(ad::Gob* Gob);
        void CheckForText(ad::Gob* Gob);
        sf::View mainView;
        std::multimap<float, sf::Drawable*> orderedDrawables;
        float globalScaleFactor;
};

} // namespace Graphics
} // namespace ad

#endif // AXOLDRIVE_GRAPHICS_GRAPHICSMANAGER_SFML_H
