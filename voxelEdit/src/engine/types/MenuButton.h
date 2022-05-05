#pragma once
#include <iostream>
#include "Block.h"
#include "Object.h"

class MenuButton {
public:
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	Object buttonObject;
	bool clickable = true;
	void(*func)(GLFWwindow* window);
	bool isHover = false;

	MenuButton() {};

	void dispButton();

	void buttonHover();

	void buttonUnhover();
};
