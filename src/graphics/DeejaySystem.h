#ifndef DEEJAYSYSTEM_H
#define DEEJAYSYSTEM_H

#include <memory>

#include "../common/PartySystem.h"




struct I_VeejaySoul: I_PartyHost {
public:
    I_VeejaySoul();
    virtual ~I_VeejaySoul();
    virtual void render() = 0;
    virtual void init() = 0;

protected:

private:
};

//***********************************************************************

struct Veejay: I_PartyHost {
public:

    enum class SoulType {OpenGL, Direct3D, SFML};

    Veejay();
    virtual ~Veejay();

    void init();
    void setSoul( SoulType );
    void update();
    void shutdown();

    //I_PartyHost interface
    void byebyeGuest( PartyGuest*, void* ) override;
    void welcomeGuest( PartyGuest*, void* ) override;


protected:

private:
    std::unique_ptr<I_VeejaySoul> djSoul;
    //I_DeejaySoul* djSoul;
};

#endif // DEEJAYSYSTEM_H
