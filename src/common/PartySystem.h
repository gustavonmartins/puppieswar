#ifndef PARTYSYSTEM_H
#define PARTYSYSTEM_H

#include <map>

struct PartyGuest;

struct I_PartyHost {
    friend struct PartyGuest;
    friend struct Veejay;

public:
    I_PartyHost();
    virtual ~I_PartyHost();

    virtual void acceptByeByeGuest_detailed( PartyGuest*, void* )               = 0; //First argument is a just fool proof against passing wrong things
    virtual void acceptByeByeGuest(PartyGuest*)                                 final;
    virtual void inviteGuest( PartyGuest* )                                     final;


protected:
    virtual void processGuest_detailed( PartyGuest*, void* )                    =0;
    //std::map<PartyGuest*, void*> GuestList;

private:
    //virtual void acceptGuest( PartyGuest*, void* )                              final; //First argument is a just fool proof against passing wrong things

};

//***************************************************************************************

struct PartyGuest {
    friend struct I_PartyHost;
public:
    PartyGuest();
    virtual ~PartyGuest();

protected:
    //virtual void initDataAddress()                                              final;
    virtual void inviteGuest( PartyGuest* myGuest )                             final;
    virtual void leaveParty()                                                   final;
    virtual void onInitData()                                                   =0;
    virtual void receiveInvitationTo( I_PartyHost* const )                      final;

    void* myData;


private:

    virtual void joinParty()                                                    final;


    bool alreadyJoined;

    I_PartyHost* myHost;
};

#endif // PARTYSYSTEM_H
