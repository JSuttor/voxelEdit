#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "controls.h"
#include "object.h"
#include "MenuButton.h"
#include "block.h"
#define mainButtonNum 2

void mainMenuLoop(GLFWwindow* window);
void initMainMenu();
void editorMenuButtonClick(GLFWwindow* window);
void exitButtonClick(GLFWwindow* window);

MenuButton mainButtonArr[mainButtonNum];
bool init = false;

void mainMenuLoop(GLFWwindow* window) {
    if (!init) {
        initMainMenu();
        init = true;
    }
    processMenuInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    for (int i = 0; i < mainButtonNum; i++) {
        //display buttons and handle potential interaction
        dispButton(mainButtonArr[i]);
        detectButtonInteract(mainButtonArr[i], window);
    }

    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

void initMainMenu() {
    //create buttons here

    mainButtonArr[0].position = glm::vec3(-18, 0.0, -25);
    mainButtonArr[0].clickable = true;
    mainButtonArr[0].func = *editorMenuButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/EditorButton.oof", mainButtonArr[0].buttonObject);

    mainButtonArr[1].position = glm::vec3(-18, -8.0, -25);
    mainButtonArr[1].clickable = true;
    mainButtonArr[1].func = *exitButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/ExitButton.oof", mainButtonArr[1].buttonObject);
}

void editorMenuButtonClick(GLFWwindow* window) {
    changeState("editor_menu", window);
}

void exitButtonClick(GLFWwindow* window) {
    //exit game
    glfwDestroyWindow(window);
    glfwTerminate();
}