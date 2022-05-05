#include "MainMenu.h"
#define mainButtonNum 2

MenuButton mainButtonArr[mainButtonNum];
bool init = false;

void mainMenuLoop(GLFWwindow* window) {
    if (!init) {
        initMainMenu();
        init = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    for (int i = 0; i < mainButtonNum; i++) {
        //display buttons and handle potential interaction
        mainButtonArr[i].dispButton();
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
    mainButtonArr[0].buttonObject.getObjectFromFile("Assets/MenuButtons/EditorButton.oof");

    mainButtonArr[1].position = glm::vec3(-18, -8.0, -25);
    mainButtonArr[1].clickable = true;
    mainButtonArr[1].func = *exitButtonClick;
    mainButtonArr[1].buttonObject.getObjectFromFile("Assets/MenuButtons/ExitButton.oof");
}

void editorMenuButtonClick(GLFWwindow* window) {
    changeState("editor_menu", window);
}

void exitButtonClick(GLFWwindow* window) {
    //exit game
    glfwDestroyWindow(window);
    glfwTerminate();
}
