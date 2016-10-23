#include "Soul_OpenGL.h"
#include <iostream>



#include <exception>

Soul_OpenGL::Soul_OpenGL() {
    //ctor
    std::cout << "Soul: I am an OPENGL SOUL!" << std::endl;

    if (GLFW_FALSE == glfwInit()) {
        std::cout << "GLFW init failed" << std::endl;
        throw std::runtime_error("GLFW init failed" );
    }

    window = glfwCreateWindow(640, 480, "Hello world!", nullptr, nullptr);
    if (nullptr == window) {
        glfwTerminate();
        std::cout << "GLFW window creation failed" << std::endl;
        throw std::runtime_error("GLFW window creation failed");
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}

Soul_OpenGL::~Soul_OpenGL() {
    std::cout << "Soul_OpenGL::~Soul_OpenGL(): AAARRGH!!!" << std::endl;

    shutdown();
}

void Soul_OpenGL::draw() {



    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        GLfloat bgcolor[] = {1.0f, 0.0f, 1.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, bgcolor);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shutdown();
}

void Soul_OpenGL::shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

//------------------------------------------INTERFACE I_DeejaySoul-----------------

void Soul_OpenGL::byebyeGuest(PartyGuest* myGuest, void* guestData) {
    if (myGuest != nullptr) {
        std::cout << "DJ Soul@GL: Bye-bye, guest!" << std::endl;
    } else {
        throw std::runtime_error("Guest to be kicked doesnt exist");
    }
}

void Soul_OpenGL::welcomeGuest(PartyGuest* myGuest, void* guestData) {
    if (myGuest != nullptr) {
        std::cout << "DJ Soul@GL: Welcome guest!" << std::endl;
    } else {
        throw std::runtime_error("Guest to be welcome doesnt exist");
    }

}

