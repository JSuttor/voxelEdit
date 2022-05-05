#include "MenuControls.h"
#include "../engine/util/Camera.h"
#include "../Globals.h"

bool firstClickMenu = true;

void detectButtonInteract(MenuButton& button, GLFWwindow* window) {
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    //set range in which cursor position will be detected as current button hover
    startX = button.position.x - 1;
    endX = startX + ((sizeof(button.buttonObject.blockStore) / sizeof(button.buttonObject.blockStore[0])) * button.buttonObject.blockSize / 100.0) + 2.0;
    startY = button.position.y - 1;
    endY = startY + ((sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])) * button.buttonObject.blockSize / 100.0) + 2.0;

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

    // obtain the world coordinates of pixel cursor is on
    GLdouble x, y, z;
    gluUnProject(mouseX, mouseY, z_cursor, modelview, projection, viewport, &x, &y, &z);

    if (x >= startX && x <= endX && y >= startY && y <= endY && z_cursor >= 0.0 && z_cursor < 1.0) {
        //do hover
        if (!button.isHover) {
            button.buttonHover();
            button.isHover = true;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && firstClickMenu) {
            //if we click
            button.func(window);
        }
    }
    else {
        //unhover
        if (button.isHover) {
            button.buttonUnhover();
            button.isHover = false;
        }
    }

    if (!(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)) {
        //just clicked
        firstClickMenu = true;
    }
    else if (button.isHover) {
        //didn't just start clicking this frame
        firstClickMenu = false;
    }
}
