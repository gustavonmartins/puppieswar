#include <stdexcept>
#include <iostream>

#include "DeejaySystem.h"

#include "gl/VeejaySoul_OpenGL.h"


I_VeejaySoul::I_VeejaySoul() {

}

I_VeejaySoul::~I_VeejaySoul() {
    std::cout << "I_DeejaySoul::~I_DeejaySoul()-> Deleting my soul!!!" << std::endl;
}

//**************************************************************************************

Veejay::Veejay() :
    djSoul( nullptr ) {
    //ctor
}

Veejay::~Veejay() {
    shutdown();
}

void Veejay::init() {
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
void Veejay::byebyeGuest( PartyGuest* myGuest, void* guestData ) {
    if ( myGuest != nullptr && guestData != nullptr && djSoul != nullptr ) {
        djSoul->byebyeGuest( myGuest, guestData );
    } else {
        throw std::runtime_error( "DJ bye bye: Null pointer" );
    }
}

void Veejay::welcomeGuest( PartyGuest* myGuest, void* guestData ) {
    if  ( myGuest != nullptr && djSoul != nullptr ) {
        std::cout << "DJ: Asking soul to welcome.." << std::endl;
        djSoul->welcomeGuest( myGuest, guestData );
    } else {
        std::cout << "myGuest: " << myGuest << std::endl;
        std::cout << "guestData: " << guestData << std::endl;

        throw std::runtime_error( "DJ welcome: Null pointer" );
    }

}

