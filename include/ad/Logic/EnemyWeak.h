#ifndef AD_LOGIC_EnemyWeak_H
#define AD_LOGIC_EnemyWeak_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class EnemyWeak : public ad::Comps::LogicComponent
{
    public:
        EnemyWeak(std::map<std::string, ad::Component*> Requires);
        void Update();

        float MoveSpeed;
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Collider* myCollider;
        bool dead;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_EnemyWeak_H
