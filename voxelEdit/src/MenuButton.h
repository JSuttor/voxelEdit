#pragma once

#include "block.h"
#include "Object.h"

struct MenuButton {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	Object buttonObject;
	bool clickable = true;
	void(*func)(GLFWwindow* window);
};

void dispButton(MenuButton button){


	for (int x = 0; x < (sizeof(button.buttonObject.blockStore)/sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				if (button.buttonObject.blockStore[x][y][z].type != 0) {
					drawCube(	(x * (float)button.buttonObject.blockSize /100.0) + button.position.x,
								(y * (float)button.buttonObject.blockSize /100.0) + button.position.y,
								(z * (float)button.buttonObject.blockSize /100.0) + button.position.z,
								button.buttonObject.blockStore[x][y][z], button.buttonObject.blockSize);
				}
			}
		}
	}
}

void buttonHover(MenuButton& button) {
	for (int x = 0; x < (sizeof(button.buttonObject.blockStore) / sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				button.buttonObject.blockStore[x][y][z].type++;
			}
		}
	}
}

void buttonUnhover(MenuButton & button) {
	for (int x = 0; x < (sizeof(button.buttonObject.blockStore) / sizeof(button.buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(button.buttonObject.blockStore[0]) / sizeof(button.buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(button.buttonObject.blockStore[0][0]) / sizeof(button.buttonObject.blockStore[0][0][0])); z++) {
				button.buttonObject.blockStore[x][y][z].type--;
			}
		}
	}
}