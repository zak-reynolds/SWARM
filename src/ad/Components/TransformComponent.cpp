#include "ad/Components/Transform.h"

namespace ad {
namespace Comps {


Transform::Transform(float x, float y, float z, float xScale, float yScale, float Rotation)
{
    this->Name = "Transform";
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->rotation = Rotation;
    this->scale[0] = xScale;
    this->scale[1] = yScale;
}

void Transform::SetTransform(float x, float y, float z, float xScale, float yScale, float Rotation)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
    this->rotation = Rotation;
    this->scale[0] = xScale;
    this->scale[1] = yScale;
}

float Transform::GetWorldX()
{
    // If parent exists (aka not being the root Gameobject)
    if (GetOwner()->Getparent() != NULL)
    {
        Transform* parentTransform = GetOwner()->Getparent()->GetTransform();
        return parentTransform->GetWorldX() + position[0];
    }
    else
    {
        return position[0];
    }
}
float Transform::GetWorldY()
{
    // If parent exists (aka not being the root Gameobject)
    if (GetOwner()->Getparent() != NULL)
    {
        Transform* parentTransform = GetOwner()->Getparent()->GetTransform();
        return parentTransform->GetWorldY() + position[1];
    }
    else
    {
        return position[1];
    }
}
float Transform::GetWorldZ()
{
    // If parent has a Transform component (aka not being the root Gameobject)
    if (GetOwner()->Getparent() != NULL)
    {
        Transform* parentTransform = GetOwner()->Getparent()->GetTransform();
        return parentTransform->GetWorldZ() + position[2];
    }
    else
    {
        return position[2];
    }
}

} // namespace Comps
} // namespace ad
