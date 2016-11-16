#ifndef GAMEVIEW_HPP_INCLUDED
#define GAMEVIEW_HPP_INCLUDED

#include "controls/GameController.hpp"


struct GameView {
    virtual ~GameView();

protected:
    GameController m_Controller;

};

#endif // GAMEVIEW_HPP_INCLUDED
