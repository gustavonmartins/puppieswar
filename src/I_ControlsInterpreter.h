#ifndef I_CONTROLSINTERPRETER_H
#define I_CONTROLSINTERPRETER_H

struct GameController;

class I_ControlsInterpreter {
public:
    I_ControlsInterpreter() {};
    virtual ~I_ControlsInterpreter() {};

    virtual void interpretControls(GameController &)=0;

protected:

private:
};

#endif // I_CONTROLSINTERPRETER_H
