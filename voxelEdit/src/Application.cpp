#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "menus/MainMenu.h"
#include "menus/EditorMenu.h"
#include "editor/Editor.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FOV 60.0

GLfloat rotateY = 0;
GLfloat rotateX = 0;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "voxelEdit", NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwMakeContextCurrent(window);

    //set flags
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glViewport(0, 0, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    gluPerspective(FOV, (13.0f/9.0f) ,0.1 ,200);  //make it so the view is in perspective instead of ortho
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        std::string gameState = getGameState();

        //for each state, enter corresponding loop
        if (gameState == "main_menu") {
            mainMenuLoop(window);
        }
        else if (gameState == "editor_menu") {
            editorMenuLoop(window);
        }
        else if (gameState == "editor") {
            editorLoop(window, gameState, screenHeight, deltaTime);
        }
    }

    glfwTerminate();
    return 0;
}
