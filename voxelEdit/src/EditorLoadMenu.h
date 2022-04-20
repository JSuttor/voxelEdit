#pragma once
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
#define editLoadButtonNum 3

void editorLoadMenuLoop(GLFWwindow* window);
void initLoadEditorMenu();
void editorLoadNewButtonClick(GLFWwindow* window);
void editorLoadMenuBackButtonClick(GLFWwindow* window);
void editorLoadObjectButtonClick(GLFWwindow* window);

MenuButton editLoadButtonArr[editLoadButtonNum];

bool editLoadInit = false;

void editorLoadMenuLoop(GLFWwindow* window) {
    if (!editLoadInit) {
        initLoadEditorMenu();
        editLoadInit = true;
    }
    processMenuInput(window);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render OpenGL here
    glPushMatrix();

    //here
    for (int i = 0; i < editLoadButtonNum; i++) {
        dispButton(editLoadButtonArr[i]);
        detectButtonInteract(editLoadButtonArr[i], window);
    }

    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

void initLoadEditorMenu() {
    editLoadButtonArr[0].position = glm::vec3(-20, 0.0, -30);
    editLoadButtonArr[0].clickable = true;
    editLoadButtonArr[0].func = *editorNewButtonClick;
    getObjectFromFile(0, "EditorButton", editLoadButtonArr[0].buttonObject);

    editLoadButtonArr[1].position = glm::vec3(-20, -10.0, -30);
    editLoadButtonArr[1].clickable = true;
    editLoadButtonArr[1].func = *editorLoadMenuBackButtonClick;
    getObjectFromFile(0, "EditorButton", editLoadButtonArr[1].buttonObject);

    editLoadButtonArr[2].position = glm::vec3(-20, 10.0, -30);
    editLoadButtonArr[2].clickable = true;
    editLoadButtonArr[2].func = *editorLoadObjectButtonClick;
    getObjectFromFile(0, "EditorButton", editLoadButtonArr[2].buttonObject);
}

void editorLoadNewButtonClick(GLFWwindow* window) {
    changeState("editor", window);
}

void editorLoadMenuBackButtonClick(GLFWwindow* window) {
    changeState("editor_menu", window);
}

void editorLoadObjectButtonClick(GLFWwindow* window) {
    //set currentOb to selected object
    std::string name = "";
    std::cout << "enter" << std::endl;
    std::cin >> name;
    std::cout << std::endl;
    Object obj;
    fillObject(obj);
    writeObjectToFile(name, obj);
    //if object is selected
    //changeState("editor", window);
}