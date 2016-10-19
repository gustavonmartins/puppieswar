#ifndef I_CONTROLSINTERPRETER_H
#define I_CONTROLSINTERPRETER_H

class GameController;

class I_ControlsInterpreter {
public:
    I_ControlsInterpreter();
    virtual ~I_ControlsInterpreter();

    virtual void interpretControls(GameController const &)=0;

protected:

private:
};

#endif // I_CONTROLSINTERPRETER_H
