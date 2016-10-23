#ifndef I_PARTYHOST_H
#define I_PARTYHOST_H

#include <vector>

class PartyGuest;

struct I_PartyHost {
public:
    I_PartyHost();
    virtual ~I_PartyHost();

    virtual void byebyeGuest(PartyGuest*,void*)=0; //First argument is a just fool proof against passing wrong things
    void inviteGuest(PartyGuest*);
    virtual void welcomeGuest(PartyGuest*, void*)=0; //First argument is a just fool proof against passing wrong things

protected:

private:
};

#endif // I_PARTYHOST_H
