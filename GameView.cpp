#include "GameView.hpp"



void GameView::run() {

    receiveFromServer();
    update();
    sendToServer();


}

void GameView::receiveFromServer() {}
void GameView::update() {}
void GameView::sendToServer() {}

GameView::~GameView(){}
