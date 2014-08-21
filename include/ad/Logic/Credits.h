#ifndef AD_LOGIC_Credits_H
#define AD_LOGIC_Credits_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class Credits : public ad::Comps::LogicComponent
{
    public:
        Credits(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Transform* swarm;
        ad::Comps::Transform* ppp;
        ad::Comps::Transform* zr;
        ad::Comps::Transform* tfp;
        ad::Comps::Transform* rest;
        float timer;
        int stage;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_Credits_H
