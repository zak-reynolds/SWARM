#ifndef AD_LOGIC_BossLogic_H
#define AD_LOGIC_BossLogic_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class BossLogic : public ad::Comps::LogicComponent
{
    public:
        BossLogic(std::map<std::string, ad::Component*> Requires);
        void Update();
        int damage;
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Collider* myCollider;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_BossLogic_H
