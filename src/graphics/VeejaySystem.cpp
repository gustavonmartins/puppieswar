#include <stdexcept>
#include <iostream>

#include "VeejaySystem.h"

#include "gl/VeejaySoul_OpenGL.h"



Veejay::Veejay() :
    djSoul( nullptr ) {
    //ctor
}

Veejay::~Veejay() {
    shutdown();
}

GameController& Veejay::getController() {
    return m_Controller;
}

void Veejay::getUserInput() {
    djSoul->getUserInput( m_Controller );
}

void Veejay::initSoul() {
    djSoul->init();
}

void Veejay::setSoul( Veejay::SoulType initTo ) {
    std::cout << "DJ: Creating my soul!" << std::endl;
    if ( initTo == Veejay::SoulType::OpenGL ) {
        djSoul = std::make_unique<VeejaySoul_OpenGL>();


    } else {}
}

void Veejay::update() {
    djSoul->render();

}

void Veejay::shutdown() {
    if ( djSoul != nullptr ) {
        std::cout << "DJ: My soul has to go!" << std::endl;
        djSoul.reset();
    } else {
        throw std::runtime_error( "DJ shutdown: DJ has no soul" );
    }
}




//************************I_PartyHost interface
void Veejay::acceptByeByeGuest_detailed( PartyGuest* myGuest, void* guestData ) {
    if ( myGuest != nullptr && guestData != nullptr && djSoul != nullptr ) {
        djSoul->acceptByeByeGuest_detailed( myGuest, guestData );
    } else {
        throw std::runtime_error( "DJ bye bye: Null pointer" );
    }
}

void Veejay::processGuest_detailed( PartyGuest* myGuest, void* guestData ) {
    if  ( myGuest != nullptr && djSoul != nullptr ) {
        std::cout << "DJ: Asking soul to welcome.." << std::endl;
        djSoul->processGuest_detailed( myGuest, guestData );
    } else {
        std::cout << "myGuest: " << myGuest << std::endl;
        std::cout << "guestData: " << guestData << std::endl;

        throw std::runtime_error( "DJ welcome: Null pointer" );
    }

}

//**************************************************************************************


I_VeejaySoul::I_VeejaySoul() {

}

I_VeejaySoul::~I_VeejaySoul() {
    std::cout << "I_DeejaySoul::~I_DeejaySoul()-> Deleting my soul!!!" << std::endl;
}
