#ifndef PARTYSYSTEM_H
#define PARTYSYSTEM_H

#include <map>

class PartyGuest;

struct I_PartyHost {
public:
    I_PartyHost();
    virtual ~I_PartyHost();

    virtual void byebyeGuest( PartyGuest*, void* ) = 0; //First argument is a just fool proof against passing wrong things
    void inviteGuest( PartyGuest* );
    virtual void welcomeGuest( PartyGuest*, void* ) = 0; //First argument is a just fool proof against passing wrong things
    void welcomeGuestPreparation( PartyGuest*, void* );


protected:
    std::map<PartyGuest*, void*> GuestList;

private:

};

struct PartyGuest {
public:
    PartyGuest();
    virtual ~PartyGuest();

    void joinParty();
    void receiveInvitationTo( I_PartyHost* const );

//protected:
    void initDataAddress( void* );
    void inviteGuest( PartyGuest* myGuest );

protected:


private:


    void leaveParty();

    bool alreadyJoined;
    void* myData;
    I_PartyHost* myHost;
};

#endif // PARTYSYSTEM_H
