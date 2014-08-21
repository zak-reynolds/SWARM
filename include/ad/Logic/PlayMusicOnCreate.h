#ifndef AD_LOGIC_PlayMusicOnCreate_H
#define AD_LOGIC_PlayMusicOnCreate_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class PlayMusicOnCreate : public ad::Comps::LogicComponent
{
    public:
        PlayMusicOnCreate(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        bool playingMusic;
        ad::Comps::Music* myMusic;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_PlayMusicOnCreate_H
