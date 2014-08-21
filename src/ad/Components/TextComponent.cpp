#include "ad/Components/Text.h"
#include "ad/Game.h"

namespace ad {
namespace Comps {

Text::Text(std::string Font, float Size, gmtl::Vec3i Color)
{
    Name = "Text";
    this->Font = Font;
    this->Size = Size;
    this->Color = Color;
    DisplayText = "";
}

Text::~Text()
{
    // Remove reference to this component from GraphicsManager
    Game.GraphicsM()->RemoveText(Owner->GetName());
}

void Text::Update()
{
}

void Text::SetTransform()
{
    transform = (ad::Comps::Transform*)GetOwnerComponent("Transform");
}

}
}

