#ifndef AD_LOGIC_DestroyAtAnimEnd_H
#define AD_LOGIC_DestroyAtAnimEnd_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class DestroyAtAnimEnd : public ad::Comps::LogicComponent
{
    public:
        DestroyAtAnimEnd(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Sprite* sc;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_DestroyAtAnimEnd_H
