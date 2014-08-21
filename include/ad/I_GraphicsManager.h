#ifndef AXOLDRIVE_GRAPHICS_I_GRAPHICSMANAGER_H
#define AXOLDRIVE_GRAPHICS_I_GRAPHICSMANAGER_H

#include "ad/Gameobject.h"
#include "ad/Math.h"
#include "ad/Containers.h"

namespace ad {
namespace Graphics {

/**
Graphics Interface:
Needs to clear screen on update,
support primitive drawing,
support blitting of png and jpg,
support Axoldrive's resource format
*/
class I_GraphicsManager
{
    public:
        virtual int Initialize() = 0;
        virtual void Update() = 0;
        virtual void Destroy() = 0;

        virtual int DrawTexture(int x, int y, std::string) = 0;
        virtual void ClearScreen() = 0;
        virtual void DrawRectangle(int x, int y, int w, int h, int r, int g, int b, int a) = 0;
        virtual void DrawCircle(int x, int y, int rad, int r, int g, int b, int a) = 0;

        virtual int LoadTexture(std::string) = 0;
        virtual int LoadTexturesAsync(ad::VectorS* Textures) = 0;
        virtual int UnloadTexture(std::string) = 0;
        virtual int LoadFont(std::string) = 0;
        virtual int UnloadFont(std::string) = 0;

        virtual void SetCurrentRootGameobject(ad::Gob* root) = 0;

        virtual void AddSprite(ad::Gob* Gob) = 0;
        virtual void RemoveSprite(std::string Gob) = 0;
        virtual void AddText(ad::Gob* Gob) = 0;
        virtual void RemoveText(std::string Gob) = 0;

        virtual float CameraX() = 0;
        virtual float CameraY() = 0;
        virtual gmtl::Vec2f CameraPosition() = 0;

        virtual gmtl::Vec2f ScreenSize() = 0;
        ad::Gob* CurrentRootGameobject;
    protected:
    private:
};

} // namespace Graphics
} // namespace ad

#endif // AXOLDRIVE_GRAPHICS_I_GRAPHICSMANAGER_H
