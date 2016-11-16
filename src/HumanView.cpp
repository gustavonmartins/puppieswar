#include "HumanView.hpp"

#include <iostream>
//#include "NetworkProtocol.hpp"
#include "Generic.hpp"

HumanView::~HumanView() {}

void HumanView::uploadPacketToAllConnected(I_Serializable::DataType* PointerToData) {
    myPostMan.uploadPacketToAllConnected(PointerToData);
}

int HumanView::tryToConnect() {
    return myPostMan.tryToConnect();
}

void HumanView::askWhereToConnect() {
    myPostMan.askWhereToConnect();
}
//****************************************************

void HumanView::init() {
    createWindow(600,400);
}

void HumanView::createWindow(unsigned int const & width,unsigned int const &  height) {

    m_RenderWindow.create(sf::VideoMode(width, height), "Human view");
    m_RenderWindow.setMouseCursorVisible(false);
    m_Camera.setCenter(0,0);
    m_Camera.zoom(1);
    m_RenderWindow.setView(m_Camera);

}

void HumanView::generateGraphics(I_ExtractableGraphics & currentGraphicsExtract) {
    generateGraphics(currentGraphicsExtract,m_RenderWindow);
}

void HumanView::generateGraphics(I_ExtractableGraphics & currentGraphicsExtract, sf::RenderWindow& _Window) {
    _Window.clear(sf::Color::White);
    extractGraphics(currentGraphicsExtract,_Window);
    _Window.display();
}

void HumanView::extractGraphics(I_ExtractableGraphics& currentGraphicsExtract,sf::RenderWindow & myWindow) {

    I_ExtractableGraphics::Output tempContentList;
    tempContentList=currentGraphicsExtract.extractGraphics();

    for (auto currentContent:tempContentList) {

        myWindow.draw(*currentContent);
    }
}
//*******************************************************************************************
GameController& HumanView::getController() {
    return m_Controller;
}

void HumanView::getUserInput() {
    getUserInput(m_RenderWindow,m_Event,m_Controller);
}

void HumanView::getUserInput(sf::RenderWindow& _Window, sf::Event & _Events, GameController& _gameController) {

    _gameController.clearControls();
//static

    if (_Window.hasFocus()) {
        WindowIsActive=true;
    } else {
        WindowIsActive=false;
    }

    if (WindowIsActive) {
        _Window.setMouseCursorVisible(false);

        myWindowCenter = static_cast<sf::Vector2i>(_Window.getSize()/2u);
        mousePosition = sf::Mouse::getPosition(_Window);
        _gameController.setMouse(mousePosition-myWindowCenter);
        sf::Mouse::setPosition(myWindowCenter,_Window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _gameController.RequestAction=true;
        } else  _gameController.RequestAction=false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            mouserightPressed=true;
            _gameController.PrepareAction2=true;
        } else if (mouserightPressed==true) {
            mouserightPressed=false;
            _gameController.RequestAction2=true;
        }
        //std::cout<<"    Finished getInputs: mouse right"<<std::endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _gameController.GoRight=true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _gameController.GoLeft=true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            _gameController.GoForward=true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _gameController.GoBack=true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _gameController.RequestJump=true;
        }

    }

    else {
        _Window.setMouseCursorVisible(true);
    }

    //std::cout<<"    Finished getInputs: declarations"<<std::endl;

    while (_Window.pollEvent(_Events)) {
        if (_Events.type == sf::Event::Closed)
            _Window.close();

        if (_Events.type==sf::Event::MouseWheelScrolled) {
            if(_Events.mouseWheelScroll.wheel==sf::Mouse::VerticalWheel) {
                _gameController.SelectNext=_Events.mouseWheelScroll.delta;
            }
        }
    }
}
