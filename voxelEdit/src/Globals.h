#pragma once
#include <iostream>
#include "engine/types/Object.h"
#include "engine/util/Controls.h"
#include "editor/EditorControls.h"

std::string gameState = "main_menu";
int screenHeight = 720;
Object currentOb;

std::string getGameState() {
    return gameState;
}
void changeState(std::string newGameState, GLFWwindow* window) {
    gameState = newGameState;
    if (gameState == "editor") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, editorMouseCallback);
    }
    if (gameState == "main_menu") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, genericMouseCallback);
    }
    if (gameState == "editor_menu") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, genericMouseCallback);
    }
}
int getScreenHeight() {
    return screenHeight;
}