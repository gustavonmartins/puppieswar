#include "PartySystem.h"

#include <iostream>

I_PartyHost::I_PartyHost() {
    //ctor
}

I_PartyHost::~I_PartyHost() {
    //dtor
}

void I_PartyHost::inviteGuest( PartyGuest* myGuest ) {
    std::cout << this << " PartHost: inviting PartyGuest" << std::endl;
    myGuest->receiveInvitationTo( this );
}

void I_PartyHost::welcomeGuestPreparation( PartyGuest* myGuest, void* initData ) {
    if ( nullptr != myGuest ) {
        std::cout << this << " Preparing to welcome guest" << std::endl;
        GuestList.insert( std::pair<PartyGuest*, void*>( myGuest, initData ) );
        welcomeGuest( myGuest, initData );
    }
    if( !initData ) {
        std::cout << this << " I see you have no data!" << std::endl;
    } else {
        std::cout << this << " Nice data!" << std::endl;
    }
}


//****************************************************************

PartyGuest::PartyGuest():
    myHost( nullptr ),
    myData( nullptr ),
    alreadyJoined( false ) {
    //ctor
}

PartyGuest::~PartyGuest() {
    leaveParty();
}

void PartyGuest::initDataAddress( void* relevantAddress ) {
    if ( relevantAddress != nullptr ) {
        myData = relevantAddress;
    }
}

void PartyGuest::inviteGuest( PartyGuest* myGuest ) {
    if ( myHost != nullptr && myGuest != nullptr ) {
        myGuest->receiveInvitationTo( myHost );
    } else {
        std::cout << "PartyGuest inviteSubGuest: nullptr" << std::endl;
    }

}

void PartyGuest::joinParty() {
    if ( myHost != nullptr && !alreadyJoined ) {
        std::cout << this << " PartyGuest: I am joining the party of " << myHost << std::endl;
        myHost->welcomeGuestPreparation( this, myData );
        alreadyJoined = true;
    } else {
        std::cout << "PartyGuest " << this << " joinParty: Cannot join cause there is no host or already joined" << std::endl;
    }

}

void PartyGuest::leaveParty() {
    if ( myHost != nullptr ) {
        std::cout << "PartyGuest: Leaving party!" << std::endl;
        myHost->byebyeGuest( this, myData );
    }
}

void PartyGuest::receiveInvitationTo( I_PartyHost* const hostAddress ) {
    if ( hostAddress != nullptr ) {
        myHost = hostAddress;
        std::cout << this << " Party Guest: I just got invited to a party at " << myHost << std::endl;
    }
    //joinParty();
}
