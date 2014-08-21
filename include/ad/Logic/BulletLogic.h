#ifndef AD_LOGIC_BulletLogic_H
#define AD_LOGIC_BulletLogic_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class BulletLogic : public ad::Comps::LogicComponent
{
    public:
        BulletLogic(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* transform;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_BulletLogic_H
