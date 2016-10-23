#ifndef I_HOOKABLETOGRAPHICS_H
#define I_HOOKABLETOGRAPHICS_H

struct I_GraphicsSystem;

class I_HookableToGraphics {
public:
    I_HookableToGraphics();
    virtual ~I_HookableToGraphics();

    virtual void hookToGraphicsSystem(I_GraphicsSystem*)=0;
    virtual void unhookToGraphicsSystem(I_GraphicsSystem*)=0;

    virtual void loadGraphics()=0;
    virtual void tickGraphics()=0;
    virtual void unloadGraphics()=0;

protected:

private:
};

#endif // I_HOOKABLETOGRAPHICS_H
