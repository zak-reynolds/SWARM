#ifndef AD_LOGIC_FXSmoke_H
#define AD_LOGIC_FXSmoke_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class FXSmoke : public ad::Comps::LogicComponent
{
    public:
        FXSmoke(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Sprite* mySprite;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_FXSmoke_H
