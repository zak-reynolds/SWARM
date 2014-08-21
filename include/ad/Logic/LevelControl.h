#ifndef AD_LOGIC_LevelControl_H
#define AD_LOGIC_LevelControl_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class LevelControl : public ad::Comps::LogicComponent
{
    public:
        LevelControl(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        int stage;
        ad::Comps::Music* musicFirst;
        ad::Comps::Music* musicBossIntro;
        ad::Comps::Music* musicBoss;
        ad::Comps::Music* musicBossTrans;
        ad::Comps::Music* musicBoss2;
        ad::Comps::Music* musicPostBoss;
        float fadeVolume;
        float timer;
        ad::Logic::BossLogic* boss;
        std::string bossstring;
        bool dualSpiral;
        int spawnCount;
        float endgameTimer;
        std::string bossProp;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_LevelControl_H
