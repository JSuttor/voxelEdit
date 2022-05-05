#pragma once

#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "MenuControls.h"
#include "../engine/types/MenuButton.h"
#include "../Globals.h"

void mainMenuLoop(GLFWwindow* window);
void initMainMenu();
void editorMenuButtonClick(GLFWwindow* window);
void exitButtonClick(GLFWwindow* window);
