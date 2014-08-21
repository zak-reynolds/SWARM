#ifndef AD_LOGIC_JUMPYTRANSFORM_H
#define AD_LOGIC_JUMPYTRANSFORM_H

#include "ad/Components.h"
#include <gmtl/gmtl.h>

namespace ad {
namespace Logic {

class JumpyTransform : public ad::Comps::LogicComponent
{
    public:
        JumpyTransform(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* transform;

        gmtl::Vec2i homePos;
        gmtl::Vec2i screenSize;
        gmtl::Vec2i imageSize;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_JUMPYTRANSFORM_H

