#ifndef AD_LOGIC_Shield_H
#define AD_LOGIC_Shield_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class Shield : public ad::Comps::LogicComponent
{
    public:
        Shield(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Collider* myCollider;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_Shield_H
