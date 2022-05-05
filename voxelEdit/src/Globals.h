#pragma once
#include <iostream>
#include "engine/types/Object.h"
#include "editor/EditorControls.h"

static int screenHeight = 720;
static Object currentOb;

static void genericMouseCallback(GLFWwindow* window, double xpos, double ypos) {};
extern void editorMouseCallback(GLFWwindow* window, double xPos, double yPos);

void changeState(std::string newGameState, GLFWwindow* window);

int getScreenHeight();

std::string getGameState();
