#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "../engine/util/Camera.h"
#include "../Globals.h"
#include "editorgrid.h"
#include "EditorControls.h"

void editorLoop(GLFWwindow* window, std::string gameState, int screenHeight, float deltaTime);
