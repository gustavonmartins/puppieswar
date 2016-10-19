#ifndef I_GRAPHICSSYSTEM_H
#define I_GRAPHICSSYSTEM_H

struct I_HookableToGraphics;

class I_GraphicsSystem {
public:

    enum class GraphicsSystemType {OpenGL,Direct3D,SFML};

    I_GraphicsSystem();
    virtual ~I_GraphicsSystem();

    virtual void hookToGraphicsSystem(I_HookableToGraphics*)=0;
    virtual void unhookToGraphicsSystem(I_HookableToGraphics*)=0;

    virtual void startGraphicsSystem(GraphicsSystemType)=0;
    virtual void renderGraphicsSystem()=0;
    virtual void shutdownGraphicsSystem()=0;


protected:

private:
};

#endif // I_GRAPHICSSYSTEM_H
