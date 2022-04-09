#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "camera.h"
#include "object.h"
#include "block.h"
#include "editorgrid.h"

void editorLoop(GLFWwindow* window, std::string gameState, int screenHeight, float deltaTime);

Object currentOb;

void editorLoop(GLFWwindow* window, std::string gameState, int screenHeight, float deltaTime) {
    if (!currentOb.init) {
        currentOb = fillObject(currentOb);
        currentOb.init = true;
    }

    processEditorInput(window, deltaTime, gameState);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render OpenGL here
    glPushMatrix();

    changeCamera();


    dispObject(currentOb);
    mouseHover(window, screenHeight);


    int size = 16;
    float edgeLength = 1.0f;
    drawGrid(size, edgeLength);


    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}