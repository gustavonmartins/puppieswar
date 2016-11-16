#include "Bullet.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>





Bullet::Bullet():
    GraphicalRadius(2) {
    //static int Instances;
    //++Instances;
    //std::cout<<"Number of bullets is: "<<Instances<<std::endl;


    GraphicalShape.setFillColor(sf::Color::Black);
    GraphicalShape.setRadius(GraphicalRadius);
}

Bullet::~Bullet() {}

void Bullet::syncGraphics() {
    GraphicalShape.setPosition(getPosition().axis_one,getPosition().axis_two);

}

I_ExtractableGraphics::Output Bullet::extractGraphics() {
    I_ExtractableGraphics::Output output;

    syncGraphics();
    output.emplace_back(&GraphicalShape);

    return output;
}

void Bullet::updateOnMainTick(double const & deltaTime) {
    move(deltaTime);
}

void Bullet::move(double const& dt) {
    Location.move(dt);
}

void Bullet::setOrientation(I_Moveable::ExchangeType& Ori) {
    Location.setOrientation(Ori);
}

void Bullet::setOrientationDelta(I_Moveable::ExchangeType& Delta) {
    Location.setOrientationDelta(Delta);
}

I_Moveable::ExchangeType& Bullet::getPosition() {
    return Location.getPosition();

}

void Bullet::setPosition(double const & _posx,double const & _posy,double const &_posz) {
    Location.setPosition(_posx, _posy,_posz);
}

void Bullet::setPosition(I_Moveable::ExchangeType& Pos) {
    Location.setPosition(Pos);
}

void Bullet::setPositionDelta(double const& deltaX, double const& deltaY, double const& deltaZ) {
    Location.setPositionDelta(deltaX,deltaY,deltaZ);
}

void Bullet::setSpeedComposition(double const& velx,double const& vely,double const& velz) {
    Location.setSpeedComposition(velx,vely,velz);
}

void Bullet::setMaxSpeed(double const& maxSpeed) {
    Location.setMaxSpeed(maxSpeed);
}

void Bullet::setOrientation(double const& angle1,double const& angle2,double const& angle3) {
    Location.setOrientation(angle1,angle2,angle3);
}

void Bullet::setOrientationDelta(double const& angle1,double const& angle2,double const& angle3) {
    Location.setOrientationDelta(angle1,angle2,angle3);
}

double& Bullet::getHeading() {
    return Location.getHeading();
}

void Bullet::setSpeedDelta(double const& velFront,double const& velLat,double const& velz) {
    Location.setSpeedDelta(velFront,velLat,velz);
}

I_Moveable::ExchangeType& Bullet::getOrientation() {
    return Location.getOrientation();
}

//************************** PARTYGUEST INTERFACE
void Bullet::onInitData() {
    myData=&Location;
}
