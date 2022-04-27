#pragma once
#include <iostream>
#include "Block.h"
#include "Object.h"

struct MenuButton {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	Object buttonObject;
	bool clickable = true;
	void(*func)(GLFWwindow* window);
	bool isHover = false;
};

void dispButton(MenuButton button){
	//display each cube of button
	for (int x = 0; x < (sizeof(button.buttonObject.blockStore)/sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				if (button.buttonObject.blockStore[x][y][z].type != 0) {
					drawCube(	(x * button.buttonObject.blockSize /100.0) + button.position.x,
								(y * button.buttonObject.blockSize /100.0) + button.position.y,
								(z * button.buttonObject.blockSize /100.0) + button.position.z,
								button.buttonObject.blockStore[x][y][z], button.buttonObject.blockSize);
				}
			}
		}
	}
}

void buttonHover(MenuButton& button) {
	//switch to lighter version of each block
	for (int x = 0; x < (sizeof(button.buttonObject.blockStore) / sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				if (button.buttonObject.blockStore[x][y][z].type != 0)
					button.buttonObject.blockStore[x][y][z].type++;
			}
		}
	}
}

void buttonUnhover(MenuButton & button) {
	//switch back to normal version of each block
	for (int x = 0; x < (sizeof(button.buttonObject.blockStore) / sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				if(button.buttonObject.blockStore[x][y][z].type != 0)
					button.buttonObject.blockStore[x][y][z].type--;
			}
		}
	}
}
