#ifndef AVATAR_HPP_INCLUDED
#define AVATAR_HPP_INCLUDED

#include <list>
#include <vector>

#include <SFML/Graphics.hpp>

#include "src/graphics/I_ExtractableGraphics.h"
#include "I_UpdateableOnMainTick.h"
#include "I_ControlsInterpreter.h"
#include "Bullet.hpp"
#include "src/controls/GameController.hpp"

#include "Moveable.hpp"
#include "I_Moveable.h"

struct Avatar:I_Moveable, I_ExtractableGraphics, I_UpdateableOnMainTick, I_ControlsInterpreter {

    Avatar();
    virtual ~Avatar();

    Avatar(const double&, const double&, const double&, const double& );

    template <typename T>
    Avatar(const double& _posx, const double& _posy, const double& _heading, const double& _SpeedTotal, T& ContainingVector) {
        ContainingVector.emplace_back(Avatar(_posx, _posy,_heading,_SpeedTotal));
    }
    template <typename T, typename R>
    Avatar(const double& _posx, const double& _posy, const double& _heading, const double& _SpeedTotal, T& ContainingVector, R& ReferencingVector) {
        Avatar(_posx, _posy, _heading, _SpeedTotal, ContainingVector);
        ReferencingVector.emplace_back(&(ContainingVector.back()));
    }

    template <typename T, typename R, typename S>
    Avatar(const double& _posx, const double& _posy, const double& _heading, const double& _SpeedTotal, T& ContainingVector, R& ReferencingVector, S& ReferencingVector2) {
        Avatar(_posx, _posy, _heading, _SpeedTotal, ContainingVector);
        ReferencingVector.emplace_back(&(ContainingVector.back()));
        ReferencingVector2.emplace_back(&(ContainingVector.back()));
    }


    template <typename T, typename R, typename S, typename U>
    Avatar(const double& _posx, const double& _posy, const double& _heading, const double& _SpeedTotal,T& ContainingVector, R& ReferencingVector, S& ReferencingVector2, U& ReferencingVector3) {
        Avatar(_posx, _posy, _heading, _SpeedTotal, ContainingVector);
        ReferencingVector.push_back(&(ContainingVector.back()));
        ReferencingVector2.emplace_back(&(ContainingVector.back()));
        ReferencingVector3.emplace_back(&(ContainingVector.back()));
    }

public:
    I_ExtractableGraphics::Output extractGraphics() override;
    void updateOnMainTick(double const &) override;

    void interpretControls(GameController const & );
    void syncGraphics();
    void setControlled(const bool& );

    void setPosition(double const &,double const &,double const &) override;
    void setPosition(I_Moveable::ExchangeType&) override;
    void setPositionDelta(double const&, double const&, double const&) override;
    void setSpeedComposition(double const &,double const &,double const &) override;
    void setSpeedDelta(double const&, double const&, double const&) override;
    void setMaxSpeed(double const &) override;
    void setOrientation(double const &,double const &,double const &) override;
    void setOrientation(ExchangeType&) override;
    void setOrientationDelta(double const &,double const &,double const &) override;
    void setOrientationDelta(ExchangeType&) override;
    void move(double const&) override;

    I_Moveable::ExchangeType& getPosition() override;
    double& getHeading() override;
    I_Moveable::ExchangeType& getOrientation() override;

private:
    double ShootRateInHerz;
    double ShootRateInSeconds;
    double TimeToWaitUntilNextShot;
    bool isFiring;
    bool isControlled;
    std::list<Bullet> ShotBullets;
    sf::ConvexShape GraphicalShape;
    sf::Color GraphicalColor;


    void shoot();

    Moveable Location;
};

#endif // AVATAR_HPP_INCLUDED
