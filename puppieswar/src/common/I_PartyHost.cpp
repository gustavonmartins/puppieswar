#include "I_PartyHost.h"

#include "src/common/PartyGuest.h"

#include <iostream>

I_PartyHost::I_PartyHost() {
    //ctor
}

I_PartyHost::~I_PartyHost() {
    //dtor
}

void I_PartyHost::inviteGuest(PartyGuest* myGuest) {
    std::cout<<"PartHost: inviting PartyGuest"<<std::endl;
    myGuest->receiveInvitationTo(this);
}
