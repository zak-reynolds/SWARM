#ifndef AD_LOGIC_PlaySoundOnCreate_H
#define AD_LOGIC_PlaySoundOnCreate_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class PlaySoundOnCreate : public ad::Comps::LogicComponent
{
    public:
        PlaySoundOnCreate(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Sound* mySound;
        bool played;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_PlaySoundOnCreate_H
