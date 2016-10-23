#ifndef PARTYGUEST_H
#define PARTYGUEST_H

#include <vector>

class I_PartyHost;

struct PartyGuest {
public:
    PartyGuest();
    virtual ~PartyGuest();

    void receiveInvitationTo(I_PartyHost* const);

//protected:
    void initDataAddress(void*);
    void inviteGuest(PartyGuest* myGuest);


private:

    void joinParty();
    void leaveParty();

    bool alreadyJoined;
    void* myData;
    I_PartyHost* myHost;
};

#endif // PARTYGUEST_H
