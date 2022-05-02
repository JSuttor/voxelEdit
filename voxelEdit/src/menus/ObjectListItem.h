#pragma once
#include "../engine/types/Block.h"
#include "../engine/types/Object.h"

struct ObjectListItem {
	Object obj; //visible item object
	void(*func)(Object obj); //function executed on item click
};

void dispItem(ObjectListItem item, int startX, int startY, int startZ);

void dispItem(ObjectListItem item, int startX, int startY, int startZ) {
	//displays list of objects on object selection menu
	int xSize = (sizeof(item.obj.blockStore) / sizeof(item.obj.blockStore[0]));
	int ySize = (sizeof(item.obj.blockStore[0]) / sizeof(item.obj.blockStore[0][0]));
	int zSize = (sizeof(item.obj.blockStore[0][0]) / sizeof(item.obj.blockStore[0][0][0]));

	//normalize object to button size
	int largest = xSize;
	if (ySize > largest) {
		largest = ySize;
	}
	if (zSize > largest) {
		largest = zSize;
	}
	int size = 500 / largest;

	//display cube by cube
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				if (item.obj.blockStore[x][y][z].type != 0) {
					item.obj.blockStore[x][y][z].drawCube((float)x * size / 100.0 + startX, (float)y * size / 100.0 + startY, (float)z * size / 100.0 + startZ, size);
				}
			}
		}
	}
}