#ifndef GAMEVIEW_HPP_INCLUDED
#define GAMEVIEW_HPP_INCLUDED

#include "controls/GameController.hpp"




struct GameView {

    virtual ~GameView();

    GameController m_Controller;

    void run();

    void update();
    void receiveFromServer();
    void sendToServer();

};

#endif // GAMEVIEW_HPP_INCLUDED
