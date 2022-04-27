#pragma once
#include <GLFW/glfw3.h>
#include "../Globals.h"
#include "../engine/types/Object.h"
#include "../engine/util/Controls.h"
#include "../engine/util/FileIO.h"

void processEditorInput(GLFWwindow* window, float delta, short& editorBlockType, Object currentOb);
void mouseEditHover(GLFWwindow* window, int screenHeight, Object& currentOb, short blockType);
void editorMouseCallback(GLFWwindow* window, double xPos, double yPos);

bool firstMouse = true;
bool firstCtrl = true;
bool firstClickEditor = true;
bool firstRightClickEditor = true;

void processEditorInput(GLFWwindow* window, float delta, short& editorBlockType, Object currentOb)
{
    float cameraSpeed = 10.0f * delta;

    //basic movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    //change block type placing TEMPORARY
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        editorBlockType = 1;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        editorBlockType = 3;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        editorBlockType = 5;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        editorBlockType = 7;
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        editorBlockType = 9;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        editorBlockType = 11;
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
        editorBlockType = 13;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        editorBlockType = 15;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        editorBlockType = 17;

    //save current object TEMPORARY
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        std::string name = "";
        std::cout << "enter" << std::endl;
        std::cin >> name;
        std::cout << std::endl;
        writeObjectToFile(name, currentOb);
    }

    //when holding control, mouse controls cursor instead of camera
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse = true;
        if (firstCtrl == true) {
            //set cursor to center of screen
            double x = SCREEN_WIDTH / 2.0;
            double y = SCREEN_HEIGHT / 2.0;
            glfwSetCursorPos(window, x, y);
            firstCtrl = false;
        }
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        firstCtrl = true;
    }
}

void editorMouseCallback(GLFWwindow* window, double xPos, double yPos) {
    if (!(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)) {
        //if control isn't held
        if (firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        //detect amount of mouse movement since last frame
        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        //mouse movement sensitivity (we'll adjust it in a settings menu later)
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        //yaw is left/right, pitch is up/down
        yaw += xoffset;
        pitch += yoffset;

        //you shouldn't be able to look up or down beyond vertical and end up upside down
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        //calc direction from pitch and yaw
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }
}

void mouseEditHover(GLFWwindow* window, int screenHeight, Object& currentOb, short blockType) {
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

        //get 3d world coordinated of pixel cursor is on
        GLfloat z_cursor;
        glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

        // obtain the world coordinates
        GLdouble x, y, z;
        gluUnProject(mouseX, mouseY, z_cursor, modelview, projection, viewport, &x, &y, &z);

        bool click = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
        bool rightClick = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

        //std::cout << z_cursor << " " << x << " " << y << " " << z << std::endl;
        editorHoverBlock(currentOb, x, y, z, z_cursor, 1, 1, 1, blockType, click && firstClickEditor, rightClick && firstRightClickEditor);
    }
    if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)) {
        //just clicked
        firstClickEditor = true;
    }
    else {
        //didn't just start clicking this frame
        firstClickEditor = false;
    }
    if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)) {
        //just right clicked
        firstRightClickEditor = true;
    }
    else {
        //didn't just start right clicking this frame
        firstRightClickEditor = false;
    }
}