#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "globals.h"
#include "MenuButton.h"
#include "Object.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void changeCamera();
void processEditorInput(GLFWwindow* window, float delta, short& editorBlockType);
void processMenuInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void editorMouseCallback(GLFWwindow* window, double xPos, double yPos);
//void menuMouseCallback(GLFWwindow* window, double xPos, double yPos);
void detectButtonInteract(MenuButton& button, GLFWwindow* window);
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

void processEditorInput(GLFWwindow* window, float delta, short &editorBlockType)
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

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        editorBlockType = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        editorBlockType = 2;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        editorBlockType = 3;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        editorBlockType = 4;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        editorBlockType = 5;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        editorBlockType = 6;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        editorBlockType = 7;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        editorBlockType = 8;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        editorBlockType = 9;

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        std::string name = "";
        std::cout << "enter" << std::endl;
        std::cin >> name;
        std::cout << std::endl;
        writeObjectToFile(name, currentOb);
    }

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

void processMenuInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (getGameState() == "menu") {
        //menuMouseCallback(window, xPos, yPos);
    }
    else if (getGameState() == "editor") {
        editorMouseCallback(window, xPos, yPos);
    }
    
}

//void menuMouseCallback(GLFWwindow* window, double xPos, double yPos) {}

void editorMouseCallback(GLFWwindow* window, double xPos, double yPos) {
    if (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)) {
        if (firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

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
void mouseEditHover(GLFWwindow* window, int screenHeight, Object currentOb) {
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

        //std::cout << z_cursor << " " << x << " " << y << " " << z << std::endl;
        editorHoverBlock(currentOb, x, y, z, z_cursor, 1, 1, 1);



    }
}

void detectButtonInteract(MenuButton &button, GLFWwindow* window) {
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    startX = button.position.x-1;
    endX = startX + (64.0 * button.buttonObject.blockSize / 100.0) + 2.0;
    startY = button.position.y-1;
    endY = startY + (32.0 * button.buttonObject.blockSize / 100.0) + 2.0;

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    mouseY = getScreenHeight() - mouseY;

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

    if (x >= startX && x <= endX && y >= startY && y <= endY && z_cursor >= 0.0 && z_cursor < 1.0) {
        //do hover
        //buttonHover(button);
            
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            button.func(window);
        }  
    }
    else {
        //buttonUnhover(button);
    }
}
