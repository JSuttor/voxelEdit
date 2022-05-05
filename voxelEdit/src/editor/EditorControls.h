#pragma once
#include <GLFW/glfw3.h>
#include "../engine/types/Object.h"


void processEditorInput(GLFWwindow* window, float delta, short& editorBlockType, Object currentOb);
void mouseEditHover(GLFWwindow* window, int screenHeight, Object& currentOb, short blockType);
void editorMouseCallback(GLFWwindow* window, double xPos, double yPos);
