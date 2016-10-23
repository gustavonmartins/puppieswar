#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED
#include <string>

#include "SFML/Graphics.hpp"

#include "graphics/I_ExtractableGraphics.h"
#include "I_UpdateableOnMainTick.h"
#include "Moveable.hpp"
#include "I_Moveable.h"


struct Bullet:I_Moveable, I_ExtractableGraphics, I_UpdateableOnMainTick {

    Bullet(const double&, const double&, const double& );

    template <typename T>
    Bullet(const double& _posx, const double& _posy, const double& _heading, T& ContainingVector) {
        ContainingVector.emplace_back(Bullet(_posx, _posy,_heading));
    }
    template <typename T, typename R>
    Bullet(const double& _posx, const double& _posy, const double& _heading, std::vector<T>& ContainingVector, std::vector<R*>& ReferencingVector) {
        Bullet(_posx, _posy, _heading, ContainingVector);
        ReferencingVector.push_back(&(ContainingVector.back()));
    }

    template <typename T, typename R, typename S>
    Bullet(const double& _posx, const double& _posy, const double& _heading, T& ContainingVector, R& ReferencingVector, S& ReferencingVector2) {
        Bullet(_posx, _posy, _heading, ContainingVector);
        ReferencingVector.push_back(&(ContainingVector.back()));
        ReferencingVector2.push_back(&(ContainingVector.back()));
    }


    template <typename T, typename R, typename S, typename U>
    Bullet(const double& _posx, const double& _posy, const double& _heading, T& ContainingVector, R& ReferencingVector, S& ReferencingVector2, U& ReferencingVector3) {
        Bullet(_posx, _posy, _heading, ContainingVector);
        ReferencingVector.push_back(&(ContainingVector.back()));
        ReferencingVector2.push_back(&(ContainingVector.back()));
        ReferencingVector3.push_back(&(ContainingVector.back()));
    }

    Bullet();
    virtual ~Bullet();

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

    I_ExtractableGraphics::Output extractGraphics() override;
    void updateOnMainTick(double const&) override;

private:
    void syncGraphics();
    double GraphicalRadius;
    sf::CircleShape GraphicalShape;
    Moveable Location;


};

#endif // BULLET_HPP_INCLUDED
