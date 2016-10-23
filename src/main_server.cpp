#include <iostream>
#include <string>
#include <memory>
#include "Game.hpp"



#include "graphics/gl/Soul_OpenGL.h"
#include "graphics/I_DeejaySoul.h"



int main2() {

    Game myGame;
    myGame.init();
    myGame.run();
    myGame.stop();
    return 0;
}

int main() {

    std::unique_ptr<I_DeejaySoul> graphicsSystem;

    graphicsSystem = std::make_unique<Soul_OpenGL>();
    graphicsSystem->draw();
    while (true) {
        ;}
}
