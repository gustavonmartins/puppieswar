#ifndef HUMAN_HPP_INCLUDED
#define HUMAN_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include "src/controls/GameController.hpp"
#include "GameView.hpp"
#include "src/graphics/I_ExtractableGraphics.h"
#include "I_Serializable.h"
#include "NetworkProtocol.hpp"
#include "PostMan.hpp"

struct HumanView: public GameView {

    virtual ~HumanView();
    HumanView() = default;
    HumanView(unsigned int const&, unsigned int const& );

    sf::Event m_Event;
    sf::RenderWindow m_RenderWindow;
    sf::View m_Camera;

    PostMan myPostMan;
    bool tryConnecting = true;

    void askWhereToConnect();
    void createWindow(unsigned int const&, unsigned int const&  );
    void generateGraphics(sf::RenderWindow&, I_ExtractableGraphics&);
    void getUserInput(sf::RenderWindow&, sf::Event&, GameController&);
    int tryToConnect();
    void uploadData(I_Serializable::DataType*);

private:
    void extractGraphics(I_ExtractableGraphics&, sf::RenderWindow&);
    sf::Vector2i mousePosition;
    sf::Vector2i myWindowCenter;

    bool WindowIsActive;
    bool mouserightPressed = false;
    std::string IPAddress;
    int Port;


};



#endif // HUMAN_HPP_INCLUDED
