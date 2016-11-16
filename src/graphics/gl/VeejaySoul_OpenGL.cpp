#include "VeejaySoul_OpenGL.h"
#include <iostream>



#include <exception>

VeejaySoul_OpenGL::VeejaySoul_OpenGL():
    mouserightPressed(false) {
    //ctor
    std::cout << "Soul: I am an OPENGL SOUL!" << std::endl;

}

VeejaySoul_OpenGL::~VeejaySoul_OpenGL() {
    std::cout << "Soul_OpenGL::~Soul_OpenGL(): AAARRGH!!!" << std::endl;
    shutdown();
}

void VeejaySoul_OpenGL::getUserInput( GameController& myController ) {

    myController.clearControls();
    glfwPollEvents ();

    glfwGetCursorPos(window,&mouseX,&mouseY);
    myController.setMouse(mouseX,mouseY);



    if ( GLFW_PRESS == glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_1 ) ) {
        myController.RequestAction = true;
    } else  {
        myController.RequestAction = false;
    }


    if ( GLFW_PRESS == glfwGetMouseButton ( window, GLFW_MOUSE_BUTTON_2 ) ) {
        mouserightPressed = true;
        myController.PrepareAction2 = true;
    } else if ( mouserightPressed == true ) {
        mouserightPressed = false;
        myController.RequestAction2 = true;
    }

    if ( GLFW_PRESS == glfwGetKey ( window, GLFW_KEY_D ) ) {
        myController.GoRight = true;
    }

    if ( GLFW_PRESS == glfwGetKey ( window, GLFW_KEY_A ) ) {
        myController.GoLeft = true;
    }

    if ( GLFW_PRESS == glfwGetKey ( window, GLFW_KEY_W ) ) {
        myController.GoForward = true;
    }

    if ( GLFW_PRESS == glfwGetKey ( window, GLFW_KEY_S ) ) {
        myController.GoBack = true;
    }

    if ( GLFW_PRESS == glfwGetKey ( window, GLFW_KEY_SPACE ) ) {
        myController.RequestJump = true;
    }
}

void VeejaySoul_OpenGL::init() {

    width=640;
    height=480;

    //*************************************************

    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    window = glfwCreateWindow( width, height, "LearnOpenGL", nullptr, nullptr );
    if ( window == nullptr ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent( window );

    gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );

//*******************************************************************

    glfwGetFramebufferSize( window, &width, &height );
    glViewport( 0, 0, width, height );



    glfwSetInputMode (window, GLFW_CURSOR ,GLFW_CURSOR_DISABLED);
//**********************************
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    initCam();

}

void VeejaySoul_OpenGL::initCam() {
    m_Cam.setLens(90, float(width) / float(height), 0.001, 10000);
    m_SC.addShader("vertex_shader.glsl", GL_VERTEX_SHADER);
    m_SC.addShader("fragment_shader.glsl", GL_FRAGMENT_SHADER);
    currentProgram= m_SC.compileProgram();

    myGeo.beCube();
    myMesh=new Mesh(&myGeo);

}

void VeejaySoul_OpenGL::render() {



    GLfloat bgcolor[] = {0.5f, 0.5f, 1.0f, 1.0f};
    glClearBufferfv( GL_COLOR, 0, bgcolor );

    static const GLfloat one = 1.0f;
    glClearBufferfv( GL_DEPTH, 0, &one );


    if (GuestList.size()==1) {

        for (I_Moveable* currentObjct:GuestList) {
            m_Cam.attachTo(currentObjct);
        }
    }

    else if (GuestList.size()>1) {
        for (I_Moveable* currentObjct:GuestList) {
            myMesh->attachToPosition(currentObjct);
            m_Cam.draw(myMesh,currentProgram);
        }
    }

    glfwSwapBuffers( window );



}

void VeejaySoul_OpenGL::shutdown() {
    glfwTerminate();
}


//------------------------------------------INTERFACE I_DeejaySoul-----------------

void VeejaySoul_OpenGL::acceptByeByeGuest_detailed( PartyGuest* myGuest, void* guestData ) {

    if ( myGuest != nullptr ) {
        std::cout << "DJ Soul@GL: Bye-bye, guest!" << std::endl;

    } else {
        throw std::runtime_error( "Guest to be kicked doesnt exist" );
    }
}

void VeejaySoul_OpenGL::processGuest_detailed( PartyGuest* myGuest, void* guestData ) {
    if ( myGuest != nullptr && guestData!=nullptr ) {
        std::cout << this << " DJ Soul@GL: Welcome guest!" << std::endl;
        std::cout<<"VeejaySoul_OpenGL::processGuest_detailed"<<std::endl;


        GuestList.emplace_back(static_cast<I_Moveable*>(guestData));

    } else {
        std::cout<<"Guest to be welcome doesnt exist"<<std::endl;
    }

}
