#include "Moveable.hpp"

#include <iostream>
#include <cmath>

Moveable::~Moveable() {}

Moveable::Moveable(const double& _posx, const double& _posy, const double& _heading, const double& _SpeedTotal):
    posx(_posx),
    posy(_posy),
    posz(0),
    Speed_xGlobal(0),
    Speed_yGlobal(0),
    Speed_zGlobal(0),
    accel_xGlobal(0),
    accel_yGlobal(0),
    accel_zGlobal(0),
    Heading(_heading),
    Pitch(0),
    MaximumSpeed(_SpeedTotal),
    SpeedLateral(0),
    SpeedFrontal(0),
    Pitch_deltaRequest(0) {

}

void Moveable::move(const double& _dt) {
    posx += Speed_xGlobal * _dt + accel_xGlobal * _dt * _dt * 0.5;
    posy += Speed_yGlobal * _dt + accel_yGlobal * _dt * _dt * 0.5;
    posz += Speed_zGlobal * _dt + accel_yGlobal * _dt * _dt * 0.5;

    Speed_xGlobal = SpeedFrontal * (cos((Heading) / 180 * 3.141516)) + SpeedLateral * (cos((Heading + 90) / 180 * 3.141516));
    Speed_yGlobal = SpeedFrontal * (sin((Heading) / 180 * 3.141516)) + SpeedLateral * (sin((Heading + 90) / 180 * 3.141516));

    static double Magnitude;
    Magnitude = std::sqrt(std::pow(Speed_xGlobal, 2) + std::pow(Speed_yGlobal, 2));
    if (Magnitude > 0) {
        Speed_xGlobal *= MaximumSpeed / Magnitude;
        Speed_yGlobal *= MaximumSpeed / Magnitude;
    }

    Speed_xGlobal += accel_xGlobal * _dt;
    Speed_yGlobal += accel_yGlobal * _dt;
    Speed_zGlobal += accel_zGlobal * _dt;

}

void Moveable::setPosition(double const& _posx, double const& _posy, double const& _posz) {
    posx = _posx;
    posy = _posy;
    posz = _posz;
}

void Moveable::setPosition(I_Moveable::ExchangeType& Pos) {
    posx = Pos.axis_one;
    posy = Pos.axis_two;
    posz = Pos.axis_three;
}

void Moveable::setPositionDelta(double const& deltaX, double const& deltaY, double const& deltaZ) {
    posx += deltaX;
    posy += deltaY;
    posz += deltaZ;
}

void Moveable::setSpeedComposition(double const& velFront, double const& velLat, double const& velz) {
    SpeedFrontal = velFront;
    SpeedLateral = velLat;
    if (0 != velz) {std::cout << "Moveable::setSpeedComposition Not supported velz:" << velz << std::endl;}
}

void Moveable::setSpeedDelta(double const& velFront, double const& velLat, double const& velz) {
    SpeedFrontal += velFront;
    SpeedLateral += velLat;
    if (0 != velz) {std::cout << "Moveable::setSpeedDelta Not supported velz:" << velz << std::endl;}
}

void Moveable::setMaxSpeed(double const& maxSpeed) {
    MaximumSpeed = maxSpeed;
}

void Moveable::setOrientation(double const& angle1, double const& angle2, double const& angle3) {
    Heading = angle1;
    Pitch = angle2;
    if (0 != angle3) {std::cout << "Moveable::setOrientation Not supported angle3:" << angle3 << std::endl;}
}

void Moveable::setOrientation(ExchangeType& Orientation) {
    Heading = Orientation.axis_one;
    Pitch = Orientation.axis_two;
}

void Moveable::setOrientationDelta(ExchangeType& OrientationDelta) {
    Heading += OrientationDelta.axis_one;
}

void Moveable::setOrientationDelta(double const& angle1, double const& angle2, double const& angle3) {
    Heading += angle1;
    Pitch += angle2;
    if (0 != angle3) {std::cout << "Moveable::setOrientationDelta Not supported angle3:" << angle3 << std::endl;}

}

double& Moveable::getHeading() {
    return Heading;
}

I_Moveable::ExchangeType& Moveable::getPosition() {
    Pos.axis_one = posx;
    Pos.axis_two = posy;
    Pos.axis_three = posz;

    return Pos;
}

I_Moveable::ExchangeType& Moveable::getOrientation() {

    Ori.axis_one = Heading;
    Ori.axis_two = Pitch;
    Ori.axis_three = 0;
    return Ori;
}
