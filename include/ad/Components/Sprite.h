#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "ad/Components/Component.h"
#include "ad/Components/Transform.h"
#include <gmtl/gmtl.h>

namespace ad {
namespace Comps {


class Sprite : public ad::Component
{
    public:
        /** Default constructor */
        Sprite(std::string Texture, gmtl::Vec2f Origin, int NumFrames, gmtl::Vec2i Size, float AnimSpeed);
        /** Default destructor */
        ~Sprite();

        void Update();

        std::string GetTexture() { return Texture; }
        // Must run this after initialization!
        void SetTransform();
        gmtl::Vec2f GetOrigin() { return origin; }
        int GetNumFrames() { return numFrames; }
        gmtl::Vec2i GetSize() { return size; }
        int GetWidth() { return size[0]; }
        int GetHeight() { return size[1]; }
        bool AnimHasPlayed() { return playedThrough; }

        float AnimSpeed;
        int AnimFrame;          /*!< 0 based */
        float Alpha;             /*!< 0-100 */
    protected:
        std::string Texture; //!< Member variable "Texture"
        ad::Comps::Transform* transform;
        gmtl::Vec2f origin;
        gmtl::Vec2i size;
        int numFrames;
        float timer;
        bool playedThrough;
    private:
};

}
}
#endif // SPRITECOMPONENT_H
