#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "controls.h"
#include "object.h"
#include "block.h"
#include "editorgrid.h"

void editorLoop(GLFWwindow* window, std::string gameState, int screenHeight, float deltaTime);
int editorSizeX = 16;
int editorSizeY = 16;
int editorSizeZ = 16;

short blockType = 1;

void editorLoop(GLFWwindow* window, std::string gameState, int screenHeight, float deltaTime) {
    if (!currentOb.init) {
        getObjectFromFile(0, "Assets/MenuButtons/LeftButton", currentOb, editorSizeX, editorSizeY, editorSizeZ);
        currentOb.init = true;
    }

    processEditorInput(window, deltaTime, blockType);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render OpenGL here
    glPushMatrix();

    changeCamera();

    dispObject(currentOb, 1, 1, 1, true);
    mouseEditHover(window, screenHeight, currentOb, blockType);

    float edgeLength = 1.0f;
    drawGrid(editorSizeX, editorSizeY, editorSizeZ, edgeLength, 1, 1, 1);

    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}