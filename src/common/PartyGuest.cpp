#include <stdexcept>

#include "PartyGuest.h"

#include "common/I_PartyHost.h"

#include <iostream>

PartyGuest::PartyGuest():
    myHost(nullptr),
    myData(nullptr),
    alreadyJoined(false) {
    //ctor
}

PartyGuest::~PartyGuest() {
    leaveParty();
}

void PartyGuest::initDataAddress(void* relevantAddress) {
    if (relevantAddress!=nullptr) {
        myData=relevantAddress;
    }
}

void PartyGuest::inviteGuest(PartyGuest* myGuest) {
    if (myHost!=nullptr && myGuest!=nullptr) {
        myGuest->receiveInvitationTo(myHost);
    } else {
        std::cout<<"PartyGuest inviteSubGuest: nullptr"<<std::endl;
    }

}

void PartyGuest::joinParty() {
    if (myHost!=nullptr && !alreadyJoined) {
        std::cout<<"PartyGuest: I am joining the party "<<std::endl;
        myHost->welcomeGuest(this,myData);
        alreadyJoined=true;
    } else {
        //std::cout<<"PartyGuest "<<this<<" joinParty: Cannot join cause there is no host or already joined"<<std::endl;
    }

}

void PartyGuest::leaveParty() {
    if (myHost!=nullptr) {
        std::cout<<"PartyGuest: Leaving party!"<<std::endl;
        myHost->byebyeGuest(this,myData);
    } else {
        throw std::runtime_error("PartyGuest leaveParty:No host to leave from");
    }
}

void PartyGuest::receiveInvitationTo(I_PartyHost* const hostAddress) {
    if (hostAddress!=nullptr) {
        myHost=hostAddress;
        std::cout<<"Party Guest: I just got invited to a party!"<<std::endl;
    }
    joinParty();
}
