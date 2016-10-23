#ifndef OPENGLHEAD_H
#define OPENGLHEAD_H

#include "graphics/I_DeejaySoul.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"


struct Soul_OpenGL: I_DeejaySoul {
public:
    Soul_OpenGL();
    virtual ~Soul_OpenGL();

    void byebyeGuest(PartyGuest*,void*) override;
    void welcomeGuest(PartyGuest*,void*) override;
    void draw() override;

protected:

private:
      GLFWwindow* window;
      void shutdown();
};

#endif // OPENGLHEAD_H
