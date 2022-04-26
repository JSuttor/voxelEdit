#pragma once
#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <vector>
#include <filesystem>
#include "controls.h"
#include "object.h"
#include "MenuButton.h"
#include "block.h"
#include "Object.h"
#include "ObjectListItem.h"
#define editButtonNum 6

std::vector<std::filesystem::directory_entry> fileNames;
ObjectListItem currentItems[16];

void editorMenuLoop(GLFWwindow* window);
void initEditorMenu();
void editorNewButtonClick(GLFWwindow* window);
void editorMenuBackButtonClick(GLFWwindow* window);
void editorLoadButtonClick(GLFWwindow* window);
void editorDeleteButtonClick(GLFWwindow* window);
void getFileNames();
void displayItems();
void getItemsFromDir();
void pageLeftClick(GLFWwindow* window);
void pageRightClick(GLFWwindow* window);
void setCurrentObject(Object obj);
int page = 0;
int maxPage;

MenuButton editButtonArr[editButtonNum];
bool editInit = false;

void editorMenuLoop(GLFWwindow* window) {
    if (!editInit) {
        initEditorMenu();
        getFileNames();
        getItemsFromDir();
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
    displayItems();

    glPopMatrix();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
}

void initEditorMenu() {
    editButtonArr[0].position = glm::vec3(-18, -5.0, -25);
    editButtonArr[0].clickable = true;
    editButtonArr[0].func = *editorNewButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/NewButton.oof", editButtonArr[0].buttonObject);

    editButtonArr[1].position = glm::vec3(-18, -11.0, -25);
    editButtonArr[1].clickable = true;
    editButtonArr[1].func = *editorMenuBackButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/BackButton.oof", editButtonArr[1].buttonObject);

    editButtonArr[2].position = glm::vec3(-18, 1.0, -25);
    editButtonArr[2].clickable = true;
    editButtonArr[2].func = *editorLoadButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/LoadButton.oof", editButtonArr[2].buttonObject);

    editButtonArr[3].position = glm::vec3(-18, 7.0, -25);
    editButtonArr[3].clickable = true;
    editButtonArr[3].func = *editorDeleteButtonClick;
    getObjectFromFile(0, "Assets/MenuButtons/DeleteButton.oof", editButtonArr[3].buttonObject);

    editButtonArr[4].position = glm::vec3(0, -13.0, -25);
    editButtonArr[4].clickable = true;
    editButtonArr[4].func = *pageLeftClick;
    getObjectFromFile(0, "Assets/MenuButtons/LeftButton.oof", editButtonArr[4].buttonObject);

    editButtonArr[5].position = glm::vec3(8, -13.0, -25);
    editButtonArr[5].position = glm::vec3(8, -13.0, -25);
    editButtonArr[5].clickable = true;
    editButtonArr[5].func = *pageRightClick;
    getObjectFromFile(0, "Assets/MenuButtons/RightButton.oof", editButtonArr[5].buttonObject);
}

void editorNewButtonClick(GLFWwindow* window) {
    changeState("editor", window);
}

void editorMenuBackButtonClick(GLFWwindow* window) {
    changeState("main_menu", window);
}

void editorLoadButtonClick(GLFWwindow* window) {
    changeState("editor", window);
}

void editorDeleteButtonClick(GLFWwindow* window) {

}

void getFileNames() {
    std::string path = "Assets/CustomObjects";
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        fileNames.push_back(entry);
    };
    maxPage = fileNames.size() / 16;
}

void displayItems() {
    int x = 0;
    int y = 0;
    int z = -25;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            x = i * 6 - 4;
            y = j * 6 - 8;
            dispItem(currentItems[index], x, y, z);
            index++;
        }
    }
}

void getItemsFromDir() {
    for (int i = 0; i < 16; i++) {
        if (page * 16 + i < fileNames.size()) {
            std::string fileName = std::filesystem::path(fileNames.at(page * 16 + i)).filename().string();
            getObjectFromFile(0, "Assets/CustomObjects/" + fileName, currentItems[i].obj);
            currentItems[i].func = *setCurrentObject;
        }
        else {
            currentItems[i].obj = {};
        }
    }
}

void setCurrentObject(Object obj) {
    currentOb = obj;
}

void pageLeftClick(GLFWwindow* window) {
    if (page != 0) {
        page--;
        getItemsFromDir();
    }
}

void pageRightClick(GLFWwindow* window) {
    if (page < maxPage) {
        page++;
        getItemsFromDir();
    }
}