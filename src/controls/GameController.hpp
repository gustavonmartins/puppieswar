#ifndef GAMECONTROLLER_HPP_INCLUDED
#define GAMECONTROLLER_HPP_INCLUDED
#include <SFML/System.hpp>

#include "../I_Serializable.h"
#include "../I_ControlsInterpreter.h"

struct GameController: I_Serializable {
    double MouseSpeed;

    bool PrepareAction;
    bool PrepareAction2;

    bool RequestAction;
    bool RequestAction2;

    bool GoLeft;
    bool GoRight;
    bool GoForward;
    bool GoBack;

    bool RequestJump;

    int SelectNext;
    int HorizontalStatus;

    GameController();
    virtual ~GameController();

    void control(I_ControlsInterpreter &) const;
    void clear(void);
    void setMouseRotation(const sf::Vector2i&);

    I_Serializable::DataType* serialize() override;
    void deserialize(I_Serializable::DataType*) override;
};

#endif // GAMECONTROLLER_HPP_INCLUDED
