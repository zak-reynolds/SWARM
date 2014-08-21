#include "ad/SFML/GraphicsManager_SFML.h"
#include "ad/Game.h"
#include "ad/Components/Sprite.h"
#include "ad/Components/Text.h"
#include "ad/Components/Transform.h"
#include <iostream>

namespace ad
{
namespace Graphics
{

GraphicsManager_SFML::GraphicsManager_SFML()
{
    Initialize();
    window = ad::Game.GetSFML_Helper()->GetmainWindow();
    mainView.reset(sf::FloatRect(0, 0, ad::Game.GetResolution()[0], ad::Game.GetResolution()[1]));
    window->setView(mainView);
    cameraTransform = NULL;
}

GraphicsManager_SFML::~GraphicsManager_SFML()
{
    //dtor
    Destroy();
}

int GraphicsManager_SFML::Initialize()
{
    return 0;
}
void GraphicsManager_SFML::Update()
{
    // DRAWING STARTS HERE
    ClearScreen();

    // Store all temporary drawables for deletion
    std::vector<sf::Drawable*> tempDrawables;
    for (auto it = orderedDrawables.begin(); it != orderedDrawables.end(); ++it)
    {
        tempDrawables.push_back(it->second);
    }

    // Iterate through all sprites; update positions and draw
    for (auto it = currentSFSprites.begin(), end = currentSFSprites.end(); it != end; ++it)
    {
        it->second->setPosition(sf::Vector2f((currentDrawableTransforms[it->first])->GetWorldX(), (currentDrawableTransforms[it->first])->GetWorldY()));
        it->second->setRotation((currentDrawableTransforms[it->first])->GetRotation());
        it->second->setScale(sf::Vector2f((currentDrawableTransforms[it->first])->GetScaleX(), (currentDrawableTransforms[it->first])->GetScaleY()));
        it->second->setColor(sf::Color(255, 255, 255, currentSprites[it->first]->Alpha * 255));

        // If animation is active
        if (currentSprites[it->first]->AnimSpeed > 0)
        {
            // Shift sprite's texture position to the correct frame
            it->second->setTextureRect(sf::IntRect(
                    currentSprites[it->first]->AnimFrame * currentSprites[it->first]->GetWidth(),
                    0,
                    currentSprites[it->first]->GetWidth(),
                    currentSprites[it->first]->GetHeight()
                                                   ));
        }

        if (currentSprites[it->first]->GetEnabled() && currentSprites[it->first]->GetOwner()->Getenabled())
            orderedDrawables.insert(std::pair<float, sf::Sprite*>((currentDrawableTransforms[it->first])->GetZ(), it->second));
    }
    for (auto it = currentSFTexts.begin(), end = currentSFTexts.end(); it != end; ++it)
    {
        it->second->setPosition(sf::Vector2f((currentDrawableTransforms[it->first])->GetWorldX(), (currentDrawableTransforms[it->first])->GetWorldY()));
        it->second->setRotation((currentDrawableTransforms[it->first])->GetRotation());
        it->second->setScale(sf::Vector2f((currentDrawableTransforms[it->first])->GetScaleX(), (currentDrawableTransforms[it->first])->GetScaleY()));

        it->second->setString(currentTexts[it->first]->DisplayText);
        it->second->setCharacterSize(currentTexts[it->first]->Size);

        orderedDrawables.insert(std::pair<float, sf::Text*>((currentDrawableTransforms[it->first])->GetZ(), it->second));
    }

    for (auto it = orderedDrawables.begin(), end = orderedDrawables.end(); it != end; ++it)
    {
        window->draw(*(it->second));
    }

    // Clean up
    while (!tempDrawables.empty())
    {
        delete tempDrawables.back();
        tempDrawables.pop_back();
    }
    tempDrawables.clear();
    orderedDrawables.clear();

    // DRAWING ENDS HERE

    if (cameraTransform != NULL)
    {
        mainView.setCenter(cameraTransform->GetWorldX(), cameraTransform->GetWorldY());
        mainView.setSize((2 - cameraTransform->GetScaleX()) * ad::Game.GetResolution()[0], (2 - cameraTransform->GetScaleX()) * ad::Game.GetResolution()[1]);
        mainView.setRotation(cameraTransform->GetRotation());
    }

    window->setView(mainView);

    // Update screen
    window->display();
}
void GraphicsManager_SFML::Destroy()
{

}

int GraphicsManager_SFML::DrawTexture(int x, int y, std::string Path)
{
    if (loadedTextures.find(Path) == loadedTextures.end())
    {
        std::cout << "Unable to draw texture; texture '" << Path << "' not loaded\n";
        return ERROR_FILENOTFOUND;
    }
    sf::Sprite sprite(loadedTextures.at(Path));
    sprite.setPosition(sf::Vector2f(x, y));
    window->draw(sprite);
    return AD_NORMALCODE;
}
void GraphicsManager_SFML::ClearScreen()
{
    window->clear();
}
void GraphicsManager_SFML::DrawRectangle(int x, int y, int w, int h, int r, int g, int b, int a)
{
    sf::RectangleShape* rec = new sf::RectangleShape();
    rec->setPosition(sf::Vector2f(x, y));
    rec->setFillColor(sf::Color(0, 0, 0, 0));
    rec->setOutlineThickness(-3);
    rec->setOutlineColor(sf::Color(r, g, b, a));
    rec->setSize(sf::Vector2f(w, h));
    orderedDrawables.insert(std::pair<float, sf::RectangleShape*>(1000, rec));
}
void GraphicsManager_SFML::DrawCircle(int x, int y, int rad, int r, int g, int b, int a)
{
    sf::CircleShape* circle = new sf::CircleShape();
    circle->setRadius(rad);
    circle->setPosition(sf::Vector2f(x - rad, y - rad));
    circle->setFillColor(sf::Color(0, 0, 0, 0));
    circle->setOutlineThickness(-1);
    circle->setOutlineColor(sf::Color(r, g, b, a));
    circle->setPointCount(50);
    orderedDrawables.insert(std::pair<float, sf::CircleShape*>(1000, circle));
}


int GraphicsManager_SFML::LoadTexture(std::string Path)
{
    if (loadedTextures.find(Path) != loadedTextures.end())
    {

        std::cout << "Didn't load texture; texture '" << Path << "' already loaded\n";
        return ERROR_FILEALREADYLOADED;
    }
    // Load texture
    sf::Texture texture;
    if (!texture.loadFromFile("Resources/Graphics/" + Path))
    {
        std::cout << "Unable to load texture: " << Path << "\n";
        return ERROR_FILENOTFOUND;
    }
    else
    {
        texture.setSmooth(true);
        std::cout << "Texture '" << Path << "' loaded properly\n";
        loadedTextures.insert( { Path, texture } );
    }
    return AD_NORMALCODE;
}

//! Called by SceneManager in working thread
int GraphicsManager_SFML::LoadTexturesAsync(ad::VectorS* Textures)
{
    sf::Context context;

    while (Textures->size() > 0)
    {
        if (loadedTextures.find(Textures->back()) != loadedTextures.end())
        {

            std::cout << "Didn't load texture; texture '" << Textures->back() << "' already loaded\n";
        }
        // Load texture
        sf::Texture texture;
        if (!texture.loadFromFile("Resources/Graphics/" + Textures->back()))
        {
            std::cout << "Unable to load texture: " << Textures->back() << "\n";
        }
        else
        {
            texture.setSmooth(true);
            std::cout << "Texture '" << Textures->back() << "' loaded properly\n";
            loadedTextures.insert( { Textures->back(), texture } );
        }
        Textures->pop_back();
    }
    delete Textures;
    return AD_NORMALCODE;
}

int GraphicsManager_SFML::UnloadTexture(std::string Path)
{
    if (loadedTextures.find(Path) == loadedTextures.end())
    {
        std::cout << "Unable to unload texture; texture '" << Path << "' not loaded\n";
        return ERROR_UNLOAD_FILENOTLOADED;
    }
    loadedTextures.erase(Path);
    return AD_NORMALCODE;
}
int GraphicsManager_SFML::LoadFont(std::string Path)
{
    if (loadedFonts.find(Path) != loadedFonts.end())
    {

        std::cout << "Didn't load font; font '" << Path << "' already loaded\n";
        return ERROR_FILEALREADYLOADED;
    }
    // Load font
    sf::Font font;
    if (!font.loadFromFile("Resources/Fonts/" + Path))
    {
        std::cout << "Unable to load font: " << Path << "\n";
        return ERROR_FILENOTFOUND;
    }
    else
    {
        std::cout << "Font '" << Path << "' loaded properly\n";
        loadedFonts.insert( { Path, font } );
    }
    return AD_NORMALCODE;
}
int GraphicsManager_SFML::UnloadFont(std::string Path)
{
    if (loadedFonts.find(Path) == loadedFonts.end())
    {
        std::cout << "Unable to unload font; font '" << Path << "' not loaded\n";
        return ERROR_UNLOAD_FILENOTLOADED;
    }
    loadedFonts.erase(Path);
    return AD_NORMALCODE;
}

void GraphicsManager_SFML::CheckForSprite(ad::Gob* Gob)
{
    // Check for Sprite components
    if (Gob->HasComponent("Sprite"))
    {
        // If it has one, load the image
        ad::Comps::Sprite* sc = (ad::Comps::Sprite*) Gob->GetComponent("Sprite");
        LoadTexture(sc->GetTexture());
        // Save Transform
        currentDrawableTransforms.insert(std::pair<std::string, ad::Comps::Transform*>(Gob->GetName(), Gob->GetTransform()));
        // Save Sprite
        currentSprites.insert(std::pair<std::string, ad::Comps::Sprite*>(Gob->GetName(), sc));
        // Create SFML Sprite object
        currentSFSprites.insert(std::pair<std::string, sf::Sprite*>(Gob->GetName(), new sf::Sprite()));
        currentSFSprites[Gob->GetName()]->setTexture(loadedTextures[sc->GetTexture()]);
        currentSFSprites[Gob->GetName()]->setPosition(sf::Vector2f(Gob->GetTransform()->GetX(), Gob->GetTransform()->GetY()));
        currentSFSprites[Gob->GetName()]->setOrigin(sf::Vector2f (sc->GetOrigin()[0], sc->GetOrigin()[1]));
        // If it's an animatable sprite
        if (sc->GetWidth() > 0) currentSFSprites[Gob->GetName()]->setTextureRect(sf::IntRect(0, sc->GetWidth(), 0, sc->GetHeight()));

        #ifdef AD_DEBUG
        std::cout <<"Sprite added for '" << Gob->GetName() << "'\n  Texture: " << sc->GetTexture() << " | X: " << Gob->GetTransform()->GetX() << " | Y: " << Gob->GetTransform()->GetY() << "\n";
        #endif
    }
    if (Gob->HasComponent("Camera"))
    {
        // Set cameraTransform
        cameraTransform = Gob->GetTransform();
    }
}
void GraphicsManager_SFML::CheckForText(ad::Gob* Gob)
{
    // Check for Text components
    if (Gob->HasComponent("Text"))
    {
        // If it has one, load the image
        ad::Comps::Text* tc = (ad::Comps::Text*) Gob->GetComponent("Text");
        LoadFont(tc->GetFont());
        // Save Transform
        currentDrawableTransforms.insert(std::pair<std::string, ad::Comps::Transform*>(Gob->GetName(), Gob->GetTransform()));
        // Save Text
        currentTexts.insert(std::pair<std::string, ad::Comps::Text*>(Gob->GetName(), tc));
        // Create SFML Text object
        currentSFTexts.insert(std::pair<std::string, sf::Text*>(Gob->GetName(), new sf::Text()));
        currentSFTexts[Gob->GetName()]->setFont(loadedFonts[tc->GetFont()]);
        currentSFTexts[Gob->GetName()]->setCharacterSize(tc->Size);
        currentSFTexts[Gob->GetName()]->setPosition(sf::Vector2f(Gob->GetTransform()->GetX(), Gob->GetTransform()->GetY()));
        currentSFTexts[Gob->GetName()]->setStyle(sf::Text::Regular);
        sf::Color c;
        c.r = tc->Color[0];
        c.g = tc->Color[1];
        c.b = tc->Color[2];
        currentSFTexts[Gob->GetName()]->setColor(c);

        #ifdef AD_DEBUG
        std::cout <<"Text added for '" << Gob->GetName() << "'\n  Font: " << tc->GetFont() << "\n";
        #endif
    }
    if (Gob->HasComponent("Camera"))
    {
        // Set cameraTransform
        cameraTransform = Gob->GetTransform();
    }
}

void GraphicsManager_SFML::AddSprite(ad::Gob* Gob)
{
    CheckForSprite(Gob);

    std::map<std::string, ad::Gob*>* children = Gob->Getchildren();
    for (auto it = children->begin(); it != children->end(); ++it)
    {
        // Iterate through children
        AddSprite(it->second);
    }
}
void GraphicsManager_SFML::AddText(ad::Gob* Gob)
{
    CheckForText(Gob);

    std::map<std::string, ad::Gob*>* children = Gob->Getchildren();
    for (auto it = children->begin(); it != children->end(); ++it)
    {
        // Iterate through children
        AddText(it->second);
    }
}

void GraphicsManager_SFML::RemoveSprite(std::string Gob)
{
    // Delete the SFML Sprite and remove references to SFML Sprite and Transform
    delete currentSFSprites[Gob];
    currentSFSprites.erase(Gob);
    // Remove reference to AD Sprite, don't delete because it's deleted by the Gob
    currentSprites.erase(Gob);
    // Don't delete Transform, the Gob does that
    currentDrawableTransforms.erase(Gob);
}
void GraphicsManager_SFML::RemoveText(std::string Gob)
{
    // Delete the SFML Sprite and remove references to SFML Sprite and Transform
    delete currentSFTexts[Gob];
    currentSFTexts.erase(Gob);
    // Remove reference to AD Sprite, don't delete because it's deleted by the Gob
    currentTexts.erase(Gob);
    // Don't delete Transform, the Gob does that
    currentDrawableTransforms.erase(Gob);
}

void GraphicsManager_SFML::SetCurrentRootGameobject(ad::Gob* root)
{
    CurrentRootGameobject = root;
    // Iterate through RootGameobject children
    AddSprite(root);
    AddText(root);
}

float GraphicsManager_SFML::CameraX()
{
    return CurrentRootGameobject->FindChildByName("Camera")->GetTransform()->GetX();
}
float GraphicsManager_SFML::CameraY()
{
    return CurrentRootGameobject->FindChildByName("Camera")->GetTransform()->GetY();
}
gmtl::Vec2f GraphicsManager_SFML::CameraPosition()
{
    return CurrentRootGameobject->FindChildByName("Camera")->GetTransform()->GetXY();
}

gmtl::Vec2f GraphicsManager_SFML::ScreenSize()
{
    return gmtl::Vec2f(window->getSize().x, window->getSize().y);
}

} // namespace Graphics
} // namespace ad

