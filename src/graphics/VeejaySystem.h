#ifndef DEEJAYSYSTEM_H
#define DEEJAYSYSTEM_H

#include <memory>
#include <map>

#include "common/PartySystem.h"
#include "controls/GameController.hpp"

struct I_VeejaySoul;

struct Veejay: I_PartyHost {
public:

    Veejay();
    virtual ~Veejay();

    enum class SoulType {
        OpenGL, Direct3D, SFML
    };

    void initSoul();
    void setSoul( SoulType );
    void update();
    void shutdown();

    void getUserInput();
    GameController& getController();



    //I_PartyHost interface
    void acceptByeByeGuest_detailed( PartyGuest*, void* ) override;
    void processGuest_detailed( PartyGuest*, void* ) override;




protected:

private:
    GameController m_Controller;
    std::unique_ptr<I_VeejaySoul> djSoul;
    //I_DeejaySoul* djSoul;
};



//***********************************************************************

struct I_VeejaySoul: I_PartyHost {
public:
    I_VeejaySoul();
    virtual ~I_VeejaySoul();
    virtual void render() = 0;
    virtual void getUserInput(GameController&)=0;
    virtual void init() = 0;

protected:

private:
};

//***********************************************************************

#endif // DEEJAYSYSTEM_H
