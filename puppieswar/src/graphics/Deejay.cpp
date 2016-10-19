#include <stdexcept>
#include <iostream>

#include "Deejay.h"

#include "src/graphics/gl/Soul_OpenGL.h"

Deejay::Deejay() :
    djSoul(nullptr) {
    //ctor
}

Deejay::~Deejay() {
    shutdown();
}

void Deejay::initSoul(Deejay::SoulType initTo) {
    std::cout<<"DJ: Creating my soul!"<<std::endl;
    if (initTo==Deejay::SoulType::OpenGL) {
        djSoul=std::make_unique<Soul_OpenGL>();
    } else {}
}

void Deejay::shutdown() {
    if (djSoul!=nullptr) {
        std::cout<<"DJ: My soul has to go!"<<std::endl;
        djSoul.reset();
    } else {
        throw std::runtime_error("DJ shutdown: DJ has no soul");
    }
}


//I_PartyHost interface
void Deejay::byebyeGuest(PartyGuest* myGuest,void* guestData) {
    if (myGuest!=nullptr && guestData!=nullptr && djSoul!=nullptr) {
        djSoul->byebyeGuest(myGuest,guestData);
    } else {
        throw std::runtime_error("DJ bye bye: Null pointer");
    }
}

void Deejay::welcomeGuest(PartyGuest* myGuest,void* guestData) {
    if  (myGuest!=nullptr && guestData!=nullptr && djSoul!=nullptr) {
        std::cout<<"DJ: Asking soul to welcome.." <<std::endl;
        djSoul->welcomeGuest(myGuest,guestData);
    } else {
        throw std::runtime_error("DJ welcome: Null pointer");
    }

}

