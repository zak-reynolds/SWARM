#include "ad/Components.h"
#include "ad/Game.h"
#include <sstream>

namespace ad {
namespace Logic {

Credits::Credits(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::Credits";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    swarm =  (ad::Comps::Transform*)Requires["CSwarmTransform"];
    ppp =  (ad::Comps::Transform*)Requires["CPPPTransform"];
    zr =  (ad::Comps::Transform*)Requires["CZRTransform"];
    tfp =  (ad::Comps::Transform*)Requires["CTfPTransform"];
    rest =  (ad::Comps::Transform*)Requires["CRestTransform"];
    timer = .5;
    stage = 0;
}

void Credits::Update()
{
    timer -= ad::Time.deltaTime();

    if (timer <= 0)
    {
        switch (stage)
        {
            case 0:
                timer = 2.4;
                // Show SWARM
                stage++;
            break;
            case 1:
                timer = 2.4;
                // Show PPP
                stage++;
            break;
            case 2:
                timer = 2.4;
                // Show ZR
                stage++;
            break;
            case 3:
                timer = 2.8;
                // Show TfP
                stage++;
            break;
            case 4:
                stage++;
            break;
        }
    }
    switch (stage)
    {
        case 0:
        break;
        case 1:
        // Swoosh in Swarm from top
        if (swarm->GetY() < -85)
        {
            swarm->MoveY(-ad::Time.deltaTime() * 2000);
        }
        if (swarm->GetY() > -85)
        {
            swarm->SetY(-85);
        }
        break;
        case 2:
        // Swoosh in PPP from bottom
        if (ppp->GetY() > 85)
        {
            ppp->MoveY(ad::Time.deltaTime() * 2000);
        }
        if (ppp->GetY() < 85)
        {
            ppp->SetY(85);
        }
        break;
        case 3:
        // Swoosh out Swarm/PPP to left
        if (swarm->GetX() > -2000)
        {
            swarm->MoveX(-ad::Time.deltaTime() * 4000);
        }
        if (ppp->GetX() > -2000)
        {
            ppp->MoveX(-ad::Time.deltaTime() * 4000);
        }
        // Swoosh in ZR from right
        if (zr->GetX() > -300)
        {
            zr->MoveX(-ad::Time.deltaTime() * 2000);
        }
        if (zr->GetX() < -300) zr->SetX(-300);
        break;
        case 4:
        // Swoosh in TfP from right
        if (tfp->GetX() > -300)
        {
            tfp->MoveX(-ad::Time.deltaTime() * 2000);
        }
        if (tfp->GetX() < -300) tfp->SetX(-300);
        break;
        case 5:
        // Start scrolling up
        zr->MoveY(ad::Time.deltaTime() * 50);
        tfp->MoveY(ad::Time.deltaTime() * 50);
        rest->MoveY(ad::Time.deltaTime() * 50);
        break;
	}
}

} // namespace Logic
} // namespace ad


