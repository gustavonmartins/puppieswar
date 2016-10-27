#ifndef DEEJAYSOUL_OPENGL_H
#define DEEJAYSOUL_OPENGL_H

#include "../DeejaySystem.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct VeejaySoul_OpenGL: I_VeejaySoul {
public:
    VeejaySoul_OpenGL();
    virtual ~VeejaySoul_OpenGL();

    //**I_VeejaySoul
    void render() override;
    void init() override;



    //**I_PartyHost
    void byebyeGuest( PartyGuest*, void* ) override;
    void welcomeGuest( PartyGuest*, void* ) override;


protected:

private:
    GLFWwindow* window;
    void shutdown();
};

#endif // DEEJAYSOUL_OPENGL_H
