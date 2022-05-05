#pragma once
#include "Object.h"

class ObjectListItem {
public:
	Object obj; //visible item object
	void(*func)(Object obj); //function executed on item click

	void dispItem(int startX, int startY, int startZ);
};
