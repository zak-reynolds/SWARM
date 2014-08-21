#ifndef AD_LOGIC_EnemyBullet_H
#define AD_LOGIC_EnemyBullet_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class EnemyBullet : public ad::Comps::LogicComponent
{
    public:
        EnemyBullet(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* transform;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_EnemyBullet_H

