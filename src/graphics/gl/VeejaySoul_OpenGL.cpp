#include "VeejaySoul_OpenGL.h"
#include <iostream>



#include <exception>

VeejaySoul_OpenGL::VeejaySoul_OpenGL() {
    //ctor
    std::cout << "Soul: I am an OPENGL SOUL!" << std::endl;

}

VeejaySoul_OpenGL::~VeejaySoul_OpenGL() {
    std::cout << "Soul_OpenGL::~Soul_OpenGL(): AAARRGH!!!" << std::endl;

    shutdown();
}



void VeejaySoul_OpenGL::init() {

    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    window = glfwCreateWindow( 640, 480, "LearnOpenGL", nullptr, nullptr );
    if ( window == nullptr ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent( window );

    gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );

    int width, height;
    glfwGetFramebufferSize( window, &width, &height );
    glViewport( 0, 0, width, height );

}

void VeejaySoul_OpenGL::render() {

    glfwPollEvents();

    GLfloat bgcolor[] = {0.5f, 0.5f, 1.0f, 1.0f};
    glClearBufferfv( GL_COLOR, 0, bgcolor );

    static const GLfloat one = 1.0f;
    glClearBufferfv( GL_DEPTH, 0, &one );

    glfwSwapBuffers( window );



}

void VeejaySoul_OpenGL::shutdown() {
    glfwTerminate();
}

//------------------------------------------INTERFACE I_DeejaySoul-----------------

void VeejaySoul_OpenGL::byebyeGuest( PartyGuest* myGuest, void* guestData ) {
    if ( myGuest != nullptr ) {
        std::cout << "DJ Soul@GL: Bye-bye, guest!" << std::endl;
    } else {
        throw std::runtime_error( "Guest to be kicked doesnt exist" );
    }
}

void VeejaySoul_OpenGL::welcomeGuest( PartyGuest* myGuest, void* guestData ) {
    if ( myGuest != nullptr ) {
        std::cout << this << " DJ Soul@GL: Welcome guest!" << std::endl;
    } else {
        throw std::runtime_error( "Guest to be welcome doesnt exist" );
    }

}

