#ifndef AD_LOGIC_FadeIn_H
#define AD_LOGIC_FadeIn_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class FadeIn : public ad::Comps::LogicComponent
{
    public:
        FadeIn(std::map<std::string, ad::Component*> Requires);
        void Update();
        float fadeTime;
    protected:
    private:
        ad::Comps::Sprite* mySprite;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_FadeIn_H
