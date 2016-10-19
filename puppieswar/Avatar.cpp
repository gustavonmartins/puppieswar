#include "Avatar.hpp"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>





Avatar::Avatar():
//    Moveable(_posx,_posy,_heading,_SpeedTotal),

    ShootRateInHerz(10.0),
    ShootRateInSeconds(1.0/ShootRateInHerz),
    TimeToWaitUntilNextShot(0.0),
    isFiring(false),
    isControlled(false) {


    GraphicalColor.r=(std::rand() %256);
    GraphicalColor.g=(std::rand() %256);
    GraphicalColor.b=(std::rand() %256);

    GraphicalShape.setPointCount(3);
    GraphicalShape.setPoint(0,sf::Vector2f(0,0));
    GraphicalShape.setPoint(1,sf::Vector2f(0,50));
    GraphicalShape.setPoint(2,sf::Vector2f(100,25));
    GraphicalShape.setOrigin(50,25);
    GraphicalShape.setFillColor(GraphicalColor);
    std::cout<<"Triangulo criado"<<std::endl;
}

Avatar::~Avatar() {}

void Avatar::interpretControls(GameController const & _gameController) {
    if (isControlled) {
        setSpeedComposition(0,0,0);
        setOrientation(_gameController.HorizontalStatus,0,0);


        if (_gameController.GoLeft) {
            setSpeedDelta(0,-1,0);
        }

        if (_gameController.GoRight) {
            setSpeedDelta(0,+1,0);
        }

        if (_gameController.GoForward) {
            setSpeedDelta(+1,0,0);
        }

        if (_gameController.GoBack) {
            setSpeedDelta(-1,0,0);
        }

        if (_gameController.RequestJump) {
            setSpeedDelta(0,0,+1);
        }

        if (_gameController.RequestAction==true) {
            shoot();
        }

        if (_gameController.SelectNext>0) {
            setControlled(false);
        }

    }

    if (_gameController.SelectNext<0) {
        setControlled(true);
    }
}

void Avatar::syncGraphics() {

    GraphicalShape.setPosition(getPosition().axis_one,getPosition().axis_two);
    GraphicalShape.setRotation(getHeading());
    GraphicalShape.setFillColor(GraphicalColor);
}

void Avatar::setControlled(const bool& input) {
    isControlled=input;
}

I_ExtractableGraphics::Output Avatar::extractGraphics() {
    I_ExtractableGraphics::Output output;

    syncGraphics();

    output.emplace_back(&GraphicalShape);

    I_ExtractableGraphics::Output output_allchild2;
    for (Bullet& currentBullet: ShotBullets) {
        output_allchild2.splice(output_allchild2.end(),currentBullet.extractGraphics());
    }
    output.splice(output.end(),output_allchild2);
    return output;
}

void Avatar::shoot() {
    if(TimeToWaitUntilNextShot<=0) {
        ShotBullets.emplace_back(Bullet());

        ShotBullets.rbegin()->setPosition(getPosition());
        ShotBullets.rbegin()->setOrientation(getOrientation());
        ShotBullets.rbegin()->setSpeedComposition(1.0,0,0);
        ShotBullets.rbegin()->setMaxSpeed(1000);

        TimeToWaitUntilNextShot=ShootRateInSeconds;
    }
}

void Avatar::updateOnMainTick(double const & deltaTime) {

    move(deltaTime);
    TimeToWaitUntilNextShot-=deltaTime;

    for (I_UpdateableOnMainTick& currentBullet:ShotBullets) {
        currentBullet.updateOnMainTick(deltaTime);
    }
}

void Avatar::move(double const& dt) {
    Location.move(dt);
}

void Avatar::setOrientation(I_Moveable::ExchangeType& Ori) {
    Location.setOrientation(Ori);
}

void Avatar::setOrientationDelta(I_Moveable::ExchangeType& Delta) {
    Location.setOrientationDelta(Delta);
}

I_Moveable::ExchangeType& Avatar::getPosition() {
    return Location.getPosition();

}

void Avatar::setPosition(double const & _posx,double const & _posy,double const &_posz) {
    Location.setPosition(_posx, _posy,_posz);
}

void Avatar::setPosition(I_Moveable::ExchangeType& Pos) {
    Location.setPosition(Pos);
}

void Avatar::setPositionDelta(double const& deltaX, double const& deltaY, double const& deltaZ) {
    Location.setPositionDelta(deltaX,deltaY,deltaZ);
}

void Avatar::setSpeedComposition(double const& velx,double const& vely,double const& velz) {
    Location.setSpeedComposition(velx,vely,velz);
}

void Avatar::setMaxSpeed(double const& maxSpeed) {
    Location.setMaxSpeed(maxSpeed);
}

void Avatar::setOrientation(double const& angle1,double const& angle2,double const& angle3) {
    Location.setOrientation(angle1,angle2,angle3);
}

void Avatar::setOrientationDelta(double const& angle1,double const& angle2,double const& angle3) {
    Location.setOrientationDelta(angle1,angle2,angle3);
}

double& Avatar::getHeading() {
    return Location.getHeading();
}

void Avatar::setSpeedDelta(double const& velFront,double const& velLat,double const& velz) {
    Location.setSpeedDelta(velFront,velLat,velz);
}

I_Moveable::ExchangeType& Avatar::getOrientation() {
    return Location.getOrientation();
}
