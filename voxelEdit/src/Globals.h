#pragma once
#include "Object.h"

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
    }
    if (gameState == "main_menu") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (gameState == "editor_menu") {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
int getScreenHeight() {
    return screenHeight;
}