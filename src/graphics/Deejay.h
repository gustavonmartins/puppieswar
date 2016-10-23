#ifndef DEEJAY_H
#define DEEJAY_H

#include <memory>

#include "common/I_PartyHost.h"
#include "graphics/I_DeejaySoul.h"

struct Deejay: I_PartyHost {
public:

    enum class SoulType {OpenGL,Direct3D,SFML};

    Deejay();
    virtual ~Deejay();

    void initSoul(SoulType);
    void shutdown();

    //I_PartyHost interface
    void byebyeGuest(PartyGuest*,void*) override;
    void welcomeGuest(PartyGuest*,void*) override;


protected:

private:
    std::unique_ptr<I_DeejaySoul> djSoul;
    //I_DeejaySoul* djSoul;
};

#endif // DEEJAY_H
