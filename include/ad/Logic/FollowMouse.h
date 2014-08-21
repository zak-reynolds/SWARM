#ifndef AD_LOGIC_FollowMouse_H
#define AD_LOGIC_FollowMouse_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class FollowMouse : public ad::Comps::LogicComponent
{
    public:
        FollowMouse(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* reticleTransform;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_FollowMouse_H
