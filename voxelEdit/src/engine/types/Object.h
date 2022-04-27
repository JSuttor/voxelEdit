#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include "block.h"

struct Object {
	Block blockStore[32][16][8]; //3d array of cubes
	byte blockSize = 100; //size of each block in object
	bool init = false; //has it been initialized?
};

void fillObject(Object &testOb);
void dispObject(Object dispOb, int startX, int startY, int startZ, bool editor = false);
void editorHoverBlock(Object& obj, double cursorX, double cursorY, double cursorZ, double z_cursor, int startX, int startY, int startZ, short blockType, bool click, bool rightClick);

void fillObject(Object &testOb) {
	//create default object with block in each corner

	testOb.blockSize = 40;
	testOb.blockStore[0][0][0] = Block{ 1 };
	testOb.blockStore[0][0][7] = Block{ 1 };
	testOb.blockStore[0][15][0] = Block{ 1 };
	testOb.blockStore[0][15][7] = Block{ 1 };
	testOb.blockStore[31][0][0] = Block{ 1 };
	testOb.blockStore[31][0][7] = Block{ 1 };
	testOb.blockStore[31][15][0] = Block{ 1 };
	testOb.blockStore[31][15][7] = Block{ 1 };
	
}

void dispObject(Object dispOb, int startX, int startY, int startZ, bool editor) {	
	//display object in world

	int blockSize;
	if (editor) {
		//in the editor, the blocksize is static
		blockSize = 100;
	}
	else {
		blockSize = dispOb.blockSize;
	}
	//display object, block by block
	for (int x = 0; x < (sizeof(dispOb.blockStore)/sizeof(dispOb.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(dispOb.blockStore[0]) / sizeof(dispOb.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(dispOb.blockStore[0][0]) / sizeof(dispOb.blockStore[0][0][0])); z++) {
				if (dispOb.blockStore[x][y][z].type != 0) {
					drawCube(	(float)x + startX, (float)y + startY, (float)z + startZ, //position
								dispOb.blockStore[x][y][z], blockSize); //color
				}
			}
		}
	}
}

void editorHoverBlock(Object &obj, double cursorX, double cursorY, double cursorZ, double z_cursor, int startX, int startY, int startZ, short blockType, bool click, bool rightClick) {

	//calculate outer bounds of object being edited
	int endX = startX + sizeof(obj.blockStore) / sizeof(obj.blockStore[0]);
	int endY = startY + sizeof(obj.blockStore[0]) / sizeof(obj.blockStore[0][0]);
	int endZ = startZ + sizeof(obj.blockStore[0][0]) / sizeof(obj.blockStore[0][0][0]);


	int intX = (int)cursorX;
	int intY = (int)cursorY;
	int intZ = (int)cursorZ;
	float xPoint = cursorX - intX;
	float yPoint = cursorY - intY;
	float zPoint = cursorZ - intZ;

	//figure out if cursor might be on a face of a cube
	bool closeToX = ((xPoint < 0.52 && xPoint > 0.48) || (xPoint > -0.52 && xPoint < -0.48));
	bool closeToY = ((yPoint < 0.52 && yPoint > 0.48) || (yPoint > -0.52 && yPoint < -0.48));
	bool closeToZ = ((zPoint < 0.52 && zPoint > 0.48) || (zPoint > -0.52 && zPoint < -0.48));
	bool found = false;
	bool hover = false;

	int finalX, finalY, finalZ, hoverX, hoverY, hoverZ;

	if (z_cursor != 1) { //if we are hovering on a block
		if (closeToX && !closeToY && !closeToZ) { //if we are on an x face
			
			int roundedY = round(cursorY);
			int roundedZ = round(cursorZ);
			int roundedX;

			//are we on a north face?
			int x1 = round(intX + 0.5);
			if (x1 >= startX && x1 < endX && roundedY >= startY && roundedY < endY && roundedZ >= startZ && roundedZ < endZ) {
				//if assuming we are on the north face will place us within the confines of the object
				if (obj.blockStore[x1-startX][roundedY-startY][roundedZ-startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedX = x1;
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX-startX;
					finalY = roundedY-startY;
					finalZ = roundedZ-startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedX = x1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
			//or a south face?
			x1 = round(intX - 0.5);
			if (x1 >= startX && x1 < endX && roundedY >= startY && roundedY < endY && roundedZ >= startZ && roundedZ < endZ) {
				//if assuming we are on the south face will place us within the confines of the object
				if (obj.blockStore[x1 - startX][roundedY - startY][roundedZ - startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedX = x1;
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX - startX;
					finalY = roundedY - startY;
					finalZ = roundedZ - startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedX = x1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
		}
		else if (!closeToX && closeToY && !closeToZ) { //if we are on a y face

			int roundedY;
			int roundedX = round(cursorX);
			int roundedZ = round(cursorZ);

			//are we on an east face?
			int y1 = round(intY + 0.5);
			if (y1 >= startY && y1 < endY && roundedX >= startX && roundedX < endX && roundedZ >= startZ && roundedZ < endZ) {
				//if assuming we are on the east face will place us within the confines of the object
				if (obj.blockStore[roundedX - startX][y1 - startY][roundedZ - startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedY = y1;
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX - startX;
					finalY = roundedY - startY;
					finalZ = roundedZ - startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedY = y1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
			//or a west face?
			y1 = round(intY - 0.5);
			if (y1 >= startY && y1 < endY && roundedX >= startX && roundedX < endX && roundedZ >= startZ && roundedZ < endZ) {
				//if assuming we are on the west face will place us within the confines of the object
				if (obj.blockStore[roundedX - startX][y1 - startY][roundedZ - startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedY = y1;
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX - startX;
					finalY = roundedY - startY;
					finalZ = roundedZ - startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedY = y1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
		}
		else if (!closeToX && !closeToY && closeToZ) { //if we are on a z face

			int roundedZ;
			int roundedX = round(cursorX);
			int roundedY = round(cursorY);

			//are we on a top face?
			int z1 = round(intZ + 0.5);
			if (z1 >= startZ && z1 < endZ && roundedX >= startX && roundedX < endX && roundedY >= startY && roundedY < endY) {
				//if assuming we are on the top face will place us within the confines of the object
				if (obj.blockStore[roundedX - startX][roundedY - startY][z1 - startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedZ = z1;
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX - startX;
					finalY = roundedY - startY;
					finalZ = roundedZ - startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedZ = z1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
			//or a bottom face?
			z1 = round(intZ - 0.5);
			if (z1 >= startZ && z1 < endZ && roundedX >= startX && roundedX < endX && roundedY >= startY && roundedY < endY) {
				//if assuming we are on the bottom face will place us within the confines of the object
				if (obj.blockStore[roundedX - startX][roundedY - startY][z1 - startZ].type == 0) {
					//if there is not a block here, then this is where we intend to place
					roundedZ = z1;\
					drawCube(roundedX, roundedY, roundedZ, Block{ blockType }, 100, true);
					found = true;
					finalX = roundedX - startX;
					finalY = roundedY - startY;
					finalZ = roundedZ - startZ;
				}
				else {
					//otherwise, this is the block we are pointing to
					roundedZ = z1;
					hover = true;
					hoverX = roundedX - startX;
					hoverY = roundedY - startY;
					hoverZ = roundedZ - startZ;
				}
			}
		}
		if (found && click) {
			//if left click frame, place in intended location
			obj.blockStore[finalX][finalY][finalZ].type = blockType;
		}
		if (hover && rightClick) {
			//if right click frame, delete block looking at
			obj.blockStore[hoverX][hoverY][hoverZ].type = 0;
		}
	}
}

