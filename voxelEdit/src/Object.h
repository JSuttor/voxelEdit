#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <ctime>
#include "block.h"

struct Object {
	glm::vec3 position = glm::vec3(0.0,0.0,0.0);
	Block blockStore[16][16][16];
	bool init = false;
};

Object fillObject(Object testOb);
void dispObject(Object dispOb);

Object fillObject(Object testOb) {
	srand(time(NULL));
	
	testOb.blockStore[0][0][0] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[0][0][15] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[0][15][0] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[0][15][15] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[15][0][0] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[15][0][15] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[15][15][0] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };
	testOb.blockStore[15][15][15] = Block{ true, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX };

	return testOb;
}

void dispObject(Object dispOb) 
{
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				if (dispOb.blockStore[x][y][z].display) {
					drawCube(	(float)x + dispOb.position.x, (float)y + dispOb.position.y, (float)z + dispOb.position.z, //position
								dispOb.blockStore[x][y][z]); //color
				}
			}
		}
	}
}