#ifndef AXOLDRIVE_COMPONENTS_TRANSFORMCOMPONENT_H
#define AXOLDRIVE_COMPONENTS_TRANSFORMCOMPONENT_H

#include "ad/Components/Component.h"
#include "ad/Math.h"

namespace ad {
namespace Comps {

class Transform : public ad::Component
{
    public:
        /** Default constructor */
        Transform(float x, float y, float z, float xScale, float yScale, float Rotation);
        /** Access Position[2]
         * \return The current value of Position[2]
         */
        void SetX(float val) { position[0] = val; }
        void SetY(float val) { position[1] = val; }
        void MoveX(float val) { position[0] += val; }
        void MoveY(float val) { position[1] -= val; }
        void SetZ(float val) { position[2] = val; }
        float GetX() { return position[0]; }
        float GetY() { return position[1]; }
        float GetZ() { return position[2]; }

        void SetPosition(gmtl::Vec3f Position) { position = Position; }
        void SetXY(gmtl::Vec2f Position) { position[0] = Position[0]; position[1] = Position[1]; }
        void MovePosition(gmtl::Vec3f Position) { position += Position; }
        gmtl::Vec3f GetPosition() { return position; }
        gmtl::Vec2f GetXY() { return gmtl::Vec2f(position[0], position[1]); }
        gmtl::Vec2f GetWorldXY() { return gmtl::Vec2f(GetWorldX(), GetWorldY()); }

        float GetRotation() { return rotation; }
        /** Set Rotation
         * \param val New value to set
         */
        void SetRotation(float val) { rotation = val; }
        /** Set Scale[1]
         * \param val New value to set
         */
        void SetScaleX(float val) { scale[0] = val; }
        void SetScaleY(float val) { scale[1] = val; }
        void SetScaleXY(float x, float y) { scale[0] = x; scale[1] = y; }
        float GetScaleX() { return scale[0]; }
        float GetScaleY() { return scale[1]; }

        float GetWorldX();
        float GetWorldY();
        float GetWorldZ();

        void SetTransform(float x, float y, float z, float xScale, float yScale, float Rotation);
    protected:
    private:
        gmtl::Vec3f position; //!< Member variable "Position[2]"
        float rotation; //!< Member variable "Rotation"
        gmtl::Vec2f scale; //!< Member variable "Scale[1]"
};

} // namespace Comps
} // namespace ad

#endif // AXOLDRIVE_COMPONENTS_TRANSFORMCOMPONENT_H
