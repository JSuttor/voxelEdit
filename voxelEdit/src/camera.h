#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void changeCamera();
void processInput(GLFWwindow* window, float delta);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
bool firstCtrl = true;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400, lastY = 300;


void changeCamera() {
	gluLookAt(  cameraPos.x, cameraPos.y, cameraPos.z, 
                cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z, 
                cameraUp.x, cameraUp.y, cameraUp.z);
}

void processEditorInput(GLFWwindow* window, float delta, std::string gameState)
{
    float cameraSpeed = 10.0f * delta;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
        if (firstCtrl == true) {
            //set cursor to center of screen
            double x = SCREEN_WIDTH / 2.0;
            double y = SCREEN_HEIGHT/2.0;
            glfwSetCursorPos(window, x, y);
            firstCtrl = false;
        }
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstCtrl = true;
    }
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }
}

void mouseHover(GLFWwindow* window, int screenHeight) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        mouseY = screenHeight - mouseY;

        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble projection[16];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        GLfloat z_cursor;
        glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

        // obtain the world coordinates
        GLdouble x, y, z;
        gluUnProject(mouseX, mouseY, z_cursor, modelview, projection, viewport, &x, &y, &z);

        std::cout << z_cursor << " " << x << " " << y << " " << z << std::endl;
    }
}
