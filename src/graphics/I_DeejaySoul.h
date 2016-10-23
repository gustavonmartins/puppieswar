#ifndef I_DEEJAYHEAD_H
#define I_DEEJAYHEAD_H

#include "src/common/I_PartyHost.h"


struct I_DeejaySoul: I_PartyHost {
public:
    I_DeejaySoul();
    virtual ~I_DeejaySoul();
    virtual void draw()=0;

protected:

private:
};

#endif // I_DEEJAYHEAD_H
