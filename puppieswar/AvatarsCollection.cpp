#include "AvatarsCollection.hpp"

#include "Generic.hpp"

#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <functional>
#include <memory>
#include <random>
#include <iostream>

AvatarsCollection::~AvatarsCollection(){}

void AvatarsCollection::updateOnMainTick(double const& dt) {
    update(dt);
    for (I_UpdateableOnMainTick& currentAvatar : ListOfAvatars) {
        currentAvatar.updateOnMainTick(dt);
    }
}

void AvatarsCollection::update(const double& _dt) {
    //interpretControls(m_GameController);
}

I_ExtractableGraphics::Output AvatarsCollection::extractGraphics() {

    I_ExtractableGraphics::Output output;


    I_ExtractableGraphics::Output output_allchild2;
    for (I_ExtractableGraphics& currentAvatar: ListOfAvatars) {
        output_allchild2.splice(output_allchild2.end(),currentAvatar.extractGraphics());
    }
    output.splice(output.end(),output_allchild2);
    return output;
}

void AvatarsCollection::interpretControls(GameController const & currentControl) {

    if (currentControl.RequestAction2==true) {
        std::cout<<"Duplicating"<<std::endl;
        ListOfAvatars.emplace_back(Avatar());
        ListOfAvatars.rbegin()->setPosition(600,300,0);
        ListOfAvatars.rbegin()->setOrientation(0,0,0);
        ListOfAvatars.rbegin()->setMaxSpeed(100);
        ListOfAvatars.rbegin()->setControlled(true);
    }

    for (I_ControlsInterpreter& currentControllable:ListOfAvatars) {
        currentControllable.interpretControls(currentControl);
    }

}
