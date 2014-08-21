#ifndef AD_LOGIC_EnemyMid_H
#define AD_LOGIC_EnemyMid_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class EnemyMid : public ad::Comps::LogicComponent
{
    public:
        EnemyMid(std::map<std::string, ad::Component*> Requires);
        void Update();

        float MoveSpeed;
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Collider* myCollider;
        bool dead;
        float timer;
        int health;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_EnemyMid_H

