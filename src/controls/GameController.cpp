#include "GameController.hpp"

#include <SFML/System.hpp>

#include "../Avatar.hpp"
#include <iostream>

#include "../NetworkProtocol.hpp"

GameController::GameController():
    MouseSpeed(0.1),
    PrepareAction(false),
    RequestAction(false),
    PrepareAction2(false),
    RequestAction2(false),
    GoLeft(false),
    GoRight(false),
    GoForward(false),
    GoBack(false),
    RequestJump(false),
    SelectNext(0),
    HorizontalStatus(0) {}

GameController::~GameController() {}

void GameController::clearControls(void) {
    PrepareAction=false;
    RequestAction=false;
    PrepareAction2=false;
    RequestAction2=false;
    GoLeft=false;
    GoRight=false;
    GoForward=false;
    GoBack=false;
    RequestJump=false;
    SelectNext=0;
}

void GameController::control(I_ControlsInterpreter & thisControllable) {
    thisControllable.interpretControls(*this);
}

void GameController::setMouse(const sf::Vector2i& _MouseInput) {
    HorizontalStatus+=_MouseInput.x*MouseSpeed;
    VerticalStatus+=_MouseInput.y*MouseSpeed;
}

void GameController::setMouseDelta(const int& xDelta,const int& yDelta) {
    HorizontalStatus+=xDelta*MouseSpeed;
    VerticalStatus+=yDelta*MouseSpeed;
}

void GameController::setMouse(const int& xPos,const int& yPos) {
    HorizontalStatus=xPos*MouseSpeed;
    VerticalStatus=yPos*MouseSpeed;
}

//};

I_Serializable::DataType* GameController::serialize() {

    networkprotocol::HeaderType myHeader;
    myHeader=static_cast<networkprotocol::HeaderType>(networkprotocol::FromClient::Controls);
    UpData<<myHeader;
    UpData<<GoBack<<GoForward<<GoLeft<<GoRight<<HorizontalStatus<<PrepareAction<<PrepareAction2<<RequestAction<<RequestAction2<<RequestJump<<SelectNext;

    return &UpData;
}
void GameController::deserialize(I_Serializable::DataType*) {}
