#ifndef I_UPDATEABLEONMAINTICK
#define I_UPDATEABLEONMAINTICK


class I_UpdateableOnMainTick {
public:
    I_UpdateableOnMainTick();
    virtual ~I_UpdateableOnMainTick();

    virtual void updateOnMainTick(double const &)=0;

protected:

private:
};

#endif // I_UPDATEABLEONMAINTICK
