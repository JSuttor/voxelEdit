#pragma once
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
#define editButtonNum 3

void editorMenuLoop(GLFWwindow* window);
void initEditorMenu();
void editorNewButtonClick(GLFWwindow* window);
void editorMenuBackButtonClick(GLFWwindow* window);
void editorLoadMenuButtonClick(GLFWwindow* window);

MenuButton editButtonArr[editButtonNum];
bool editInit = false;

void editorMenuLoop(GLFWwindow* window) {
    if (!editInit) {
        initEditorMenu();
        editInit = true;
    }
    processMenuInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render OpenGL here
    glPushMatrix();

    //here
    for (int i = 0; i < editButtonNum; i++) {
        dispButton(editButtonArr[i]);
        detectButtonInteract(editButtonArr[i], window);
    }

    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

void initEditorMenu() {
    editButtonArr[0].position = glm::vec3(-10, 0.0, -30);
    editButtonArr[0].clickable = true;
    editButtonArr[0].func = *editorNewButtonClick;
    getObjectFromFile(0, "EditorButton", editButtonArr[0].buttonObject);

    editButtonArr[1].position = glm::vec3(-10, -10.0, -30);
    editButtonArr[1].clickable = true;
    editButtonArr[1].func = *editorMenuBackButtonClick;
    getObjectFromFile(0, "EditorButton", editButtonArr[1].buttonObject);

    editButtonArr[2].position = glm::vec3(-10, 10.0, -30);
    editButtonArr[2].clickable = true;
    editButtonArr[2].func = *editorLoadMenuButtonClick;
    getObjectFromFile(0, "EditorButton", editButtonArr[2].buttonObject);
}

void editorNewButtonClick(GLFWwindow* window) {
    changeState("editor", window);
}

void editorMenuBackButtonClick(GLFWwindow* window) {
    changeState("main_menu", window);
}

void editorLoadMenuButtonClick(GLFWwindow* window) {
    changeState("editor_load_menu", window);
}