#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "globals.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void changeCamera();
void genericMouseCallback(GLFWwindow* window, double xpos, double ypos);

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400, lastY = 300;

void changeCamera() {
    //move camera position and direction based on current variables
	gluLookAt(  cameraPos.x, cameraPos.y, cameraPos.z, 
                cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z, 
                cameraUp.x, cameraUp.y, cameraUp.z);
}

void genericMouseCallback(GLFWwindow* window, double xpos, double ypos) {};