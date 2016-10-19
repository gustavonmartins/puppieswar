#include "HumanView.hpp"

#include <iostream>
//#include "NetworkProtocol.hpp"
#include "Generic.hpp"

HumanView::~HumanView(){}




void HumanView::uploadData(I_Serializable::DataType* PointerToData) {
    myPostMan.uploadPacketToAllConnected(PointerToData);
}

int HumanView::tryToConnect() {

    return myPostMan.connectTo(IPAddress,Port,sf::Time::Zero);


}

void HumanView::askWhereToConnect() {

    std::cout<<"Enter server port to connect to: "<<std::endl;
    std::cin>>Port;
    std::cout<<"Enter server addres to connect to: "<<std::endl;
    std::cin>>IPAddress;
    std::cout<<"Ok, got info! "<<std::endl;

}

HumanView::HumanView(unsigned int const & width,unsigned int const &  height) {

    m_RenderWindow.create(sf::VideoMode(width, height), "Human view");
    m_RenderWindow.setView(m_Camera);

}

void HumanView::createWindow(unsigned int const & width,unsigned int const &  height) {

    m_RenderWindow.create(sf::VideoMode(width, height), "Human view");
    m_RenderWindow.setMouseCursorVisible(false);
    m_RenderWindow.setView(m_Camera);

}

void HumanView::generateGraphics(sf::RenderWindow& _Window, I_ExtractableGraphics & currentGraphicsExtract) {
    _Window.clear(sf::Color::White);
    extractGraphics(currentGraphicsExtract,_Window);
    _Window.display();
}

void HumanView::getUserInput(sf::RenderWindow& _Window, sf::Event & _Events, GameController& _gameController) {

    _gameController.clear();
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
        _gameController.setMouseRotation(mousePosition-myWindowCenter);
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
        } else {
            _gameController.GoRight=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            _gameController.GoLeft=true;
        } else {
            _gameController.GoLeft=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            _gameController.GoForward=true;
        } else {
            _gameController.GoForward=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _gameController.GoBack=true;
        }  else {
            _gameController.GoBack=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            _gameController.RequestJump=true;
        }  else {
            _gameController.RequestJump=false;
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

void HumanView::extractGraphics(I_ExtractableGraphics& currentGraphicsExtract,sf::RenderWindow & myWindow) {

    I_ExtractableGraphics::Output tempContentList;
    tempContentList=currentGraphicsExtract.extractGraphics();

    for (auto currentContent:tempContentList) {

        myWindow.draw(*currentContent);
    }
}
