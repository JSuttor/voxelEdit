#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "block.h"

class Object {
public:
	Block blockStore[32][16][8]; //3d array of cubes
	byte blockSize = 100; //size of each block in object
	bool init = false; //has it been initialized?

	Object() {};

	void fillObject();

	void dispObject(int startX, int startY, int startZ, bool editor);

	void editorHoverBlock(double cursorX, double cursorY, double cursorZ, double z_cursor, int startX, int startY, int startZ, short blockType, bool click, bool rightClick);

	void getObjectFromFile(std::string name, int& xSize, int& ySize, int& zSize);

	void getObjectFromFile(std::string name);

	int writeObjectToFile(std::string name);
};
