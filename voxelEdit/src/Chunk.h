#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "block.h"
#include "object.h"

struct Chunk{
	Block blocks[16][16][16];
};

void displayChunk(Chunk dispChunk);

void displayChunk(Chunk dispChunk){
		for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				if (dispChunk.blocks[x][y][z].display) {
					drawCube((float)x + testOb.position.x, (float)y + testOb.position.y, (float)z + testOb.position.z, //position
								testOb.blockStore[x][y][z].size, //size
								testOb.blockStore[x][y][z].red, testOb.blockStore[x][y][z].blue, testOb.blockStore[x][y][z].green); //color
				}
			}
		}
	}
}