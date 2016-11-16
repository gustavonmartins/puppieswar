#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "controls/GameController.hpp"
#include "GameView.hpp"
#include "graphics/I_ExtractableGraphics.h"
#include "I_Serializable.h"
#include "NetworkProtocol.hpp"
#include "PostMan.hpp"


struct HumanView: public GameView {

    virtual ~HumanView();
    HumanView() = default;


    sf::Event m_Event;
    sf::RenderWindow m_RenderWindow;
    sf::View m_Camera;

    PostMan myPostMan;
    void askWhereToConnect();
    bool tryConnecting = true;
    int tryToConnect();
    void uploadPacketToAllConnected(I_Serializable::DataType*);


    void init();

    void generateGraphics( I_ExtractableGraphics&);

    void getUserInput();
    GameController& getController();



private:

    void createWindow( unsigned int const&, unsigned int const&  );

    void extractGraphics(I_ExtractableGraphics&, sf::RenderWindow&);
    void generateGraphics(I_ExtractableGraphics&, sf::RenderWindow&);
    void getUserInput(sf::RenderWindow&, sf::Event&, GameController&);

    sf::Vector2i mousePosition;
    sf::Vector2i myWindowCenter;

    bool WindowIsActive;
    bool mouserightPressed = false;
};


#endif // HUMAN_HPP_INCLUDED
