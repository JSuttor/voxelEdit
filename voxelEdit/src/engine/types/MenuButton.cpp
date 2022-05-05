#include "MenuButton.h"

void MenuButton::dispButton() {
	//display each cube of button
	for (int x = 0; x < (sizeof(buttonObject.blockStore) / sizeof(buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(buttonObject.blockStore[0]) / sizeof(buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(buttonObject.blockStore[0][0]) / sizeof(buttonObject.blockStore[0][0][0])); z++) {
				if (buttonObject.blockStore[x][y][z].type != 0) {
					buttonObject.blockStore[x][y][z].drawCube((x * buttonObject.blockSize / 100.0) + position.x,
						(y * buttonObject.blockSize / 100.0) + position.y,
						(z * buttonObject.blockSize / 100.0) + position.z,
						buttonObject.blockSize);
				}
			}
		}
	}
}

void MenuButton::buttonHover() {
	//switch to lighter version of each block
	for (int x = 0; x < (sizeof(buttonObject.blockStore) / sizeof(buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(buttonObject.blockStore[0]) / sizeof(buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(buttonObject.blockStore[0][0]) / sizeof(buttonObject.blockStore[0][0][0])); z++) {
				if (buttonObject.blockStore[x][y][z].type != 0)
					buttonObject.blockStore[x][y][z].type++;
			}
		}
	}
}

void MenuButton::buttonUnhover() {
	//switch back to normal version of each block
	for (int x = 0; x < (sizeof(buttonObject.blockStore) / sizeof(buttonObject.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(buttonObject.blockStore[0]) / sizeof(buttonObject.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(buttonObject.blockStore[0][0]) / sizeof(buttonObject.blockStore[0][0][0])); z++) {
				if (buttonObject.blockStore[x][y][z].type != 0)
					buttonObject.blockStore[x][y][z].type--;
			}
		}
	}
}
