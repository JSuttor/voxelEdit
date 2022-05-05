#include "ObjectListItem.h"

#include "Block.h"

void ObjectListItem::dispItem(int startX, int startY, int startZ) {
	//displays list of objects on object selection menu
	int xSize = (sizeof(obj.blockStore) / sizeof(obj.blockStore[0]));
	int ySize = (sizeof(obj.blockStore[0]) / sizeof(obj.blockStore[0][0]));
	int zSize = (sizeof(obj.blockStore[0][0]) / sizeof(obj.blockStore[0][0][0]));

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
				if (obj.blockStore[x][y][z].type != 0) {
					obj.blockStore[x][y][z].drawCube((float)x * size / 100.0 + startX, (float)y * size / 100.0 + startY, (float)z * size / 100.0 + startZ, size);
				}
			}
		}
	}
}