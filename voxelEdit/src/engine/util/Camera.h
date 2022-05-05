#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Camera {
private:
    Camera() = default;
    ~Camera() = default;
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;
public:
    static Camera& getInstance() {
        static Camera instance;
        return instance;
    };

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastX = 400, lastY = 300;

    void changeCamera();

    static void genericMouseCallback(GLFWwindow* window, double xpos, double ypos) {};
};
