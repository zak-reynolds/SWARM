#include "ad/Components/Sprite.h"
#include "ad/Game.h"

namespace ad {
namespace Comps {

Sprite::Sprite(std::string Texture, gmtl::Vec2f Origin, int NumFrames, gmtl::Vec2i Size, float AnimSpeed)
{
    Name = "Sprite";
    this->Texture = Texture;
    origin = Origin;
    numFrames = NumFrames;
    size = Size;
    this->AnimSpeed = AnimSpeed;

    if (AnimSpeed > 0) timer = 1 / AnimSpeed;
    else timer = 0;
    AnimFrame = 0;

    playedThrough = false;
    Alpha = 1;
}

Sprite::~Sprite()
{
    // Remove reference to this component from GraphicsManager
    Game.GraphicsM()->RemoveSprite(Owner->GetName());
}

void Sprite::Update()
{
    if (AnimSpeed > 0)
    {
        timer -= ad::Time.deltaTime();

        if (timer <= 0)
        {
            AnimFrame++;
            if (AnimFrame == numFrames)
            {
                AnimFrame = 0;
                playedThrough = true;
            }
            timer += 1 / AnimSpeed;
        }
    }
}

void Sprite::SetTransform()
{
    transform = (ad::Comps::Transform*)GetOwnerComponent("Transform");
}

}
}
