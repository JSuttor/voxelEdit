#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>

#define red 0.1f
#define green 0.1f
#define blue 0.1f
#define opacity 0.5f

void drawGrid(int size, float edgeLength);

void drawGrid(int size, float edgeLength) {

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    GLfloat halfSideLength = edgeLength * 0.5f;
    int x = 0, y = 0, z = 0;
    
    //draw horizontal lines across x axis
    for (int x = 0; x < size; x++) {
        for (int y = -1; y < size; y++) {
            for (int z = -1; z < size; z++) {
                GLfloat vertices[] =
                {
                    x - halfSideLength, y + halfSideLength, z + halfSideLength,
                    x + halfSideLength, y + halfSideLength, z + halfSideLength,


                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(red, green, blue, opacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }
    
    //draw vertical lines
    for (int x = -1; x < size; x++) {
        for (int y = 0; y < size; y++) {
            for (int z = -1; z < size; z++) {
                GLfloat vertices[] =
                {
                    x + halfSideLength, y - halfSideLength, z + halfSideLength,
                    x + halfSideLength, y + halfSideLength, z + halfSideLength,


                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(red, green, blue, opacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }

    //draw horizontal lines across z axis
    for (int x = -1; x < size; x++) {
        for (int y = -1; y < size; y++) {
            for (int z = 0; z < size; z++) {
                GLfloat vertices[] =
                {
                    x + halfSideLength, y + halfSideLength, z - halfSideLength,
                    x + halfSideLength, y + halfSideLength, z + halfSideLength,


                };
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glColor4f(red, green, blue, opacity);
                glEnableClientState(GL_VERTEX_ARRAY);
                glVertexPointer(3, GL_FLOAT, 0, vertices);

                glDrawArrays(GL_LINES, 0, 2);
                glDisableClientState(GL_VERTEX_ARRAY);
            }
        }
    }
}
