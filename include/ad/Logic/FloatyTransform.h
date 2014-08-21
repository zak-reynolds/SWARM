#ifndef AD_LOGIC_FLOATYTRANSFORM_H
#define AD_LOGIC_FLOATYTRANSFORM_H

#include "ad/Components.h"
#include <ad/Math.h>

namespace ad {
namespace Logic {

class FloatyTransform : public ad::Comps::LogicComponent
{
    public:
        FloatyTransform(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* transform;
        gmtl::Vec2f lastFramePos;
        gmtl::Vec2f homePos;
        gmtl::Vec2f targetPos;
        gmtl::Vec2f velocity;
        float targetScale;

        float intensity;
        int constrain;
        float turnspeed;
        float resetdistance;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_FLOATYTRANSFORM_H
