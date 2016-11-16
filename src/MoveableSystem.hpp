#ifndef MOVEABLE_HPP_INCLUDED
#define MOVEABLE_HPP_INCLUDED

#include <vector>

class I_Moveable {
public:
    I_Moveable();
    virtual ~I_Moveable();


    struct CS_3D {
        double axis_one;
        double axis_two;
        double axis_three;

        CS_3D(double const&, double const&, double const&);
        CS_3D() = default;
    };


    typedef CS_3D ExchangeType;

    virtual void setPosition(double const&, double const&, double const&) = 0;
    virtual void setPosition(ExchangeType&) = 0;
    virtual void setPositionDelta(double const&, double const&, double const&) = 0;
    virtual void setSpeedComposition(double const&, double const&, double const&) = 0;
    virtual void setSpeedDelta(double const&, double const&, double const&) = 0;
    virtual void setMaxSpeed(double const&) = 0;
    virtual void setOrientation(double const&, double const&, double const&) = 0;
    virtual void setOrientation(ExchangeType&) = 0;
    virtual void setOrientationDelta(double const&, double const&, double const&) = 0;
    virtual void setOrientationDelta(ExchangeType&) = 0;
    virtual void move(double const&) = 0;

    virtual ExchangeType& getPosition() = 0;
    virtual double& getHeading() = 0;
    virtual ExchangeType& getOrientation() = 0;



protected:

private:
};

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
