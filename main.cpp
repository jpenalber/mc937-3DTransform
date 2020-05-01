#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include"cube.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 970

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

GLfloat translationX = 0.0f;
GLfloat translationY = 0.0f;
bool translation_active = false;

int selectedCube = 0;
std::vector<Cube> cubes;

int main( void )
{
    GLFWwindow *window;

    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL );

    glfwSetKeyCallback( window, keyCallback );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, 1 );


    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glClearColor(0.2f, 0.2f, 0.5f, 0.f);

    glViewport( translationX, translationY, screenWidth, screenHeight ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment

    GLfloat halfScreenWidth = SCREEN_WIDTH / 6;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 6;

    Cube *cube = new Cube();
    cube->setVertices(halfScreenWidth, halfScreenHeight, -500, 200);
    cube->select();
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(3*halfScreenWidth, halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(5*halfScreenWidth, halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(halfScreenWidth, 3*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(3*halfScreenWidth, 3*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(5*halfScreenWidth, 3*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(halfScreenWidth, 5*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(3*halfScreenWidth, 5*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);
    cube = new Cube();
    cube->setVertices(5*halfScreenWidth, 5*halfScreenHeight, -500, 200);
    cubes.push_back(*cube);


    // Loop until the user closes the window
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );

        // Render OpenGL here
        glViewport( translationX, translationY, screenWidth, screenHeight );
        for (Cube c : cubes) {
            c.Draw();
        }


        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );
    }

    glfwTerminate( );

    return 0;
}

void selectALL(){
    for(std::vector<Cube>::iterator c = cubes.begin(); c != cubes.end(); ++c) {
        c->select();
        c->selectAll();
    }
}

void diselectALL(){
    for(std::vector<Cube>::iterator c = cubes.begin(); c != cubes.end(); ++c) {
        c->diselect();
        c->diselectAll();
    }
}

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    std::cout << key << std::endl;

    const GLfloat rotationSpeed = 10;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if ( action == GLFW_PRESS || action == GLFW_REPEAT ) {
        switch (key) {

            // Toggle camera mode
            case GLFW_KEY_C:
                translation_active = !translation_active;
                break;

            // Cube selection
            case GLFW_KEY_0:
                selectALL();
                selectedCube = -1;
                break;

            case GLFW_KEY_1:
            case GLFW_KEY_2:
            case GLFW_KEY_3:
            case GLFW_KEY_4:
            case GLFW_KEY_5:
            case GLFW_KEY_6:
            case GLFW_KEY_7:
            case GLFW_KEY_8:
            case GLFW_KEY_9:
                if (selectedCube == -1) {
                    diselectALL();
                } else {
                    cubes[selectedCube].diselect();
                }
                selectedCube = key-GLFW_KEY_0-1;
                cubes[selectedCube].select();
                break;

            // Scaling

            // Rotation
            case GLFW_KEY_S:
                std::cout << "rotate the selected cube aroud the x-axis" << std::endl;
                break;
            case GLFW_KEY_Q:
                std::cout << "rotate the selected cube aroud the y-axis" << std::endl;
                break;
            case GLFW_KEY_A:
                std::cout << "rotate the selected cube aroud the z-axis" << std::endl;
                break;

            // Translation
        }

        std::cout << "selectedCube: " << selectedCube << std::endl;

        if (translation_active) {
            switch ( key )
            {
                case GLFW_KEY_UP:
                    translationY += rotationSpeed;
                    break;
                case GLFW_KEY_DOWN:
                    translationY -= rotationSpeed;
                    break;
                case GLFW_KEY_RIGHT:
                    translationX += rotationSpeed;
                    break;
                case GLFW_KEY_LEFT:
                    translationX -= rotationSpeed;
                    break;
            }
        }
    }
}

