#include "Globals.h"

std::string gameState = "main_menu";

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

std::string getGameState() {
    return gameState;
}
