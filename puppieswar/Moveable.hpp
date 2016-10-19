#ifndef MOVEABLE_HPP_INCLUDED
#define MOVEABLE_HPP_INCLUDED

#include <vector>
#include "I_Moveable.h"

struct Moveable:I_Moveable {

    Moveable()=default;
    Moveable(const double&, const double&, const double&, const double& );

    virtual ~Moveable();

    void setPosition(double const &,double const &,double const &) override;
    void setPosition(I_Moveable::ExchangeType&) override;
    void setPositionDelta(double const &,double const &,double const &) override;
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
    double posx;
    double posy;
    double posz;

    double Speed_xGlobal;
    double Speed_yGlobal;
    double Speed_zGlobal;

    double accel_xGlobal;
    double accel_yGlobal;
    double accel_zGlobal;

    double Heading;
    double Pitch;

    //Non-Downloadable:

    double MaximumSpeed;
    double SpeedLateral;
    double SpeedFrontal;

    double Pitch_deltaRequest;

    I_Moveable::ExchangeType Pos;
    I_Moveable::ExchangeType Vel;
    I_Moveable::ExchangeType Acc;
    I_Moveable::ExchangeType Ori;
};

#endif // MOVEABLE_HPP_INCLUDED
