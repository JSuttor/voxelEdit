#pragma once
#include "block.h"
#include "Object.h"

struct ObjectListItem {
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	Object obj;
	bool clickable;
	void(*func)(GLFWwindow* window);
};

void dispItem(ObjectListItem item);

void dispItem(ObjectListItem item) {
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 32; y++) {
			for (int z = 0; z < 8; z++) {
				if (item.obj.blockStore[x][y][z].type != 0) {
					drawCube(((float)x * 0.2f) + item.position.x,
						((float)y * 0.2f) + item.position.y,
						((float)z * 0.2f) + item.position.z,
						item.obj.blockStore[x][y][z], 20);
				}
			}
		}
	}
}