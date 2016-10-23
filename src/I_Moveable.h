#ifndef I_MOVEABLE_H
#define I_MOVEABLE_H


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

#endif // I_MOVEABLE_H
