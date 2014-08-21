#ifndef AD_LOGIC_ShipControl_H
#define AD_LOGIC_ShipControl_H

#include "ad/Components.h"
#include "ad/Math.h"

namespace ad {
namespace Logic {

class ShipControl : public ad::Comps::LogicComponent
{
    public:
        ShipControl(std::map<std::string, ad::Component*> Requires);
        void Update();

        float topSpeed;
        float acceleration;
        float deceleration;
        float turnspeed;
        float bulletRate;

        float DamageLevel;
    protected:
    private:
        gmtl::Vec2f velocity;
        float speed;
        gmtl::Vec2f targetDirection;
        ad::Comps::Transform* shipTransform;

        int bulletCount;
        float bulletTimer;

        float fxTimer;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_ShipControl_H
