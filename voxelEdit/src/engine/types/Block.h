#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>

//ALL DATA MUST BE BYTES

struct typeEntry {
    byte red = 0;
    byte green = 0;
    byte blue = 0;
    byte alpha = 255;
};

static typeEntry typeTable[65536] = {
    {}, //nothing
    {150, 150, 150, 255}, //stone
    {180, 180, 180, 255}, //stoneLight
    {55, 191, 69, 255}, //grass
    {100, 227, 113, 255}, //grassLight
    {140, 90, 52, 255}, //dirt
    {173, 120, 80, 255}, //dirtLight
    {73, 163, 242, 255}, //sky
    {131, 193, 247, 255}, //skyLight
    {}, //glass
};

class Block {
public:
    short type = 0;

    Block(short initType);

    Block();

    void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, byte size);

    void drawCube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, byte size, bool hover);
};
