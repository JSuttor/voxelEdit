#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <vector>
#include <filesystem>
#include "MenuControls.h"
#include "../engine/types/ObjectListItem.h"
#include "../engine/types/MenuButton.h"
#include "../Globals.h"

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
