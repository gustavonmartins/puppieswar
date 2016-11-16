#ifndef GAMESTATUS_HPP_INCLUDED
#define GAMESTATUS_HPP_INCLUDED

#include <SFML/Audio.hpp>

#include "controls/GameController.hpp"
#include "GameView.hpp"
#include "I_UpdateableOnMainTick.h"
#include "I_ControlsInterpreter.h"
#include "Avatar.hpp"
#include "common/PartySystem.h"


struct AvatarsCollection: I_ControlsInterpreter, I_ExtractableGraphics, I_UpdateableOnMainTick, PartyGuest  {

private:
    void update(const double& _dt);

    std::list<Avatar> ListOfAvatars;


public:

    virtual ~AvatarsCollection();

    GameController m_GameController;

    void updateOnMainTick(double const& dt) override;
    I_ExtractableGraphics::Output extractGraphics() override;
    void interpretControls(GameController &) override;

    void onInitData()   override;

};

#endif // GAMESTATUS_HPP_INCLUDED
