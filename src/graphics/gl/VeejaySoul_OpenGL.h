#ifndef VEEJAYSOUL_OPENGL_H
#define VEEJAYSOUL_OPENGL_H

#include "../VeejaySystem.h"
#include "graphics/gl/Camera.h"
#include "graphics/gl/Mesh.h"

#include "MoveableSystem.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/gl/ShaderCompiler.h"


struct VeejaySoul_OpenGL: I_VeejaySoul {
public:
    VeejaySoul_OpenGL();
    virtual ~VeejaySoul_OpenGL();

    //**I_VeejaySoul
    void getUserInput(GameController&) override;
    void render() override;
    void init() override;





    //**I_PartyHost
    void acceptByeByeGuest_detailed( PartyGuest*, void* ) override;
    void processGuest_detailed( PartyGuest*, void* ) override;


protected:

private:
    GLFWwindow* window;
    Camera m_Cam;
    void shutdown();
    bool mouserightPressed;
    ShaderCompiler m_SC;
    GLuint currentProgram;

    void initCam();


    int width, height;
    double mouseX, mouseY;

    std::vector<I_Moveable*> GuestList;

    Mesh* myMesh;
    MeshGeometry myGeo;

};

#endif // VEEJAYSOUL_OPENGL_H
