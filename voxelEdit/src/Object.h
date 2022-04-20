#pragma once
#include <GLFW/glfw3.h>
#include <windows.h>
#include <math.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <ctime>
#include <fstream>
#include "block.h"

struct Object {
	Block blockStore[32][16][8];
	byte blockSize = 100;
	bool init = false;
};

void fillObject(Object &testOb);
void dispObject(Object dispOb, int startX, int startY, int startZ);
void editorHoverBlock(Object obj, double x, double y, double z, double z_cursor);
void getObjectFromFile(int index, std::string name, Object& obj, int& xSize, int& ySize, int& zSize);
void getObjectFromFile(int index, std::string name, Object& obj);
int writeObjectToFile(std::string name, Object obj);

void fillObject(Object &testOb) {
	/*
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				testOb.blockStore[x][y][z] = Block{ 2 };
			}
		}
	}
	*/
	//testOb.blockStore[7][7][7] = Block{ 2 };

	testOb.blockSize = 30;
	testOb.blockStore[0][0][0] = Block{ 2 };
	testOb.blockStore[0][0][7] = Block{ 2 };
	testOb.blockStore[0][15][0] = Block{ 2 };
	testOb.blockStore[0][15][7] = Block{ 2 };
	testOb.blockStore[31][0][0] = Block{ 2 };
	testOb.blockStore[31][0][7] = Block{ 2 };
	testOb.blockStore[31][15][0] = Block{ 2 };
	testOb.blockStore[31][15][7] = Block{ 2 };
	
}

void dispObject(Object dispOb, int startX, int startY, int startZ) 
{
	for (int x = 0; x < (sizeof(dispOb.blockStore)/sizeof(dispOb.blockStore[0])); x++) {
		for (int y = 0; y < (sizeof(dispOb.blockStore[0]) / sizeof(dispOb.blockStore[0][0])); y++) {
			for (int z = 0; z < (sizeof(dispOb.blockStore[0][0]) / sizeof(dispOb.blockStore[0][0][0])); z++) {
				if (dispOb.blockStore[x][y][z].type != 0) {
					drawCube(	(float)x + startX, (float)y + startY, (float)z + startZ, //position
								dispOb.blockStore[x][y][z], dispOb.blockSize); //color
				}
			}
		}
	}
}

void getObjectFromFile(int index, std::string name, Object &obj, int &xSize, int &ySize, int &zSize) {
	obj.init = true;
	
	std::ifstream fin;
	fin.open(name + ".oof", std::ios::binary | std::ios::in);

	char ch;
	fin.read(&ch, 1);
	xSize = ch;
	fin.read(&ch, 1);
	ySize = ch;
	fin.read(&ch, 1);
	zSize = ch;
	fin.read(&ch, 1);
	obj.blockSize = ch;
	short type;

	char *sh = new char[2];

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				fin.read(sh, 2);
				type = sh[1];
				type = type << 8;
				type = sh[0] | type;
				obj.blockStore[x][y][z].type = type;
			}
		}
	}
	fin.close();
}

void getObjectFromFile(int index, std::string name, Object& obj) {
	obj.init = true;

	int xSize, ySize, zSize;

	std::ifstream fin;
	fin.open(name + ".oof", std::ios::binary | std::ios::in);

	char ch;
	fin.read(&ch, 1);
	xSize = ch;
	fin.read(&ch, 1);
	ySize = ch;
	fin.read(&ch, 1);
	zSize = ch;
	fin.read(&ch, 1);
	obj.blockSize = ch;
	short type;

	char* sh = new char[2];

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				fin.read(sh, 2);
				type = sh[1];
				type = type << 8;
				type = sh[0] | type;
				obj.blockStore[x][y][z].type = type;
			}
		}
	}
	fin.close();
}

int writeObjectToFile(std::string name, Object obj) {
	int place = 0;

	std::ofstream fout;
	fout.open(name + ".oof", std::ios::out |  std::ios::binary );

	byte xSize = sizeof(obj.blockStore) / sizeof(obj.blockStore[0]);
	byte ySize = sizeof(obj.blockStore[0]) / sizeof(obj.blockStore[0][0]);
	byte zSize = sizeof(obj.blockStore[0][0]) / sizeof(obj.blockStore[0][0][0]);

	fout << xSize;
	fout << ySize;
	fout << zSize;
	fout << obj.blockSize;

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				short temp = obj.blockStore[x][y][z].type;
				char a = temp & 0xFF;
				temp = temp >> 8;
				char b = temp;
				fout.write(&a, 1);
				fout.write(&b, 1);
			}
		}
	}
	fout.close();

	return place;
}


void editorHoverBlock(Object obj, double cursorX, double cursorY, double cursorZ, double z_cursor, int startX, int startY, int startZ) {

	int endX = startX + sizeof(obj.blockStore) / sizeof(obj.blockStore[0]);
	int endY = startY + sizeof(obj.blockStore[0]) / sizeof(obj.blockStore[0][0]);
	int endZ = startZ + sizeof(obj.blockStore[0][0]) / sizeof(obj.blockStore[0][0][0]);


	int intX = (int)cursorX;
	int intY = (int)cursorY;
	int intZ = (int)cursorZ;
	float xPoint = cursorX - intX;
	float yPoint = cursorY - intY;
	float zPoint = cursorZ - intZ;

	bool closeToX = ((xPoint < 0.52 && xPoint > 0.48) || (xPoint > -0.52 && xPoint < -0.48));
	bool closeToY = ((yPoint < 0.52 && yPoint > 0.48) || (yPoint > -0.52 && yPoint < -0.48));
	bool closeToZ = ((zPoint < 0.52 && zPoint > 0.48) || (zPoint > -0.52 && zPoint < -0.48));

	if (z_cursor != 1) {
		if (closeToX && !closeToY && !closeToZ) {
			
			int roundedY = round(cursorY);
			int roundedZ = round(cursorZ);
			int roundedX;

			int x1 = round(intX + 0.5);
			if (x1 >= startX && x1 < endX && roundedY >= startY && roundedY < endY && roundedZ >= startZ && roundedZ < endZ) {
				if (obj.blockStore[x1-startX][roundedY-startY][roundedZ-startZ].type == 0) {
					roundedX = x1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
			x1 = round(intX - 0.5);
			if (x1 >= startX && x1 < endX && roundedY >= startY && roundedY < endY && roundedZ >= startZ && roundedZ < endZ) {
				if (obj.blockStore[x1 - startX][roundedY - startY][roundedZ - startZ].type == 0) {
					roundedX = x1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
		}
		else if (!closeToX && closeToY && !closeToZ) {

			int roundedY;
			int roundedX = round(cursorX);
			int roundedZ = round(cursorZ);

			int y1 = round(intY + 0.5);
			if (y1 >= startY && y1 < endY && roundedX >= startX && roundedX < endX && roundedZ >= startZ && roundedZ < endZ) {
				if (obj.blockStore[roundedX - startX][y1 - startY][roundedZ - startZ].type == 0) {
					roundedY = y1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
			y1 = round(intY - 0.5);
			if (y1 >= startY && y1 < endY && roundedX >= startX && roundedX < endX && roundedZ >= startZ && roundedZ < endZ) {
				if (obj.blockStore[roundedX - startX][y1 - startY][roundedZ - startZ].type == 0) {
					roundedY = y1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
		}
		else if (!closeToX && !closeToY && closeToZ) {

			int roundedZ;
			int roundedX = round(cursorX);
			int roundedY = round(cursorY);

			int z1 = round(intZ + 0.5);
			if (z1 >= startZ && z1 < endZ && roundedX >= startX && roundedX < endX && roundedY >= startY && roundedY < endY) {
				if (obj.blockStore[roundedX - startX][roundedY - startY][z1 - startZ].type == 0) {
					roundedZ = z1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
			z1 = round(intZ - 0.5);
			if (z1 >= startZ && z1 < endZ && roundedX >= startX && roundedX < endX && roundedY >= startY && roundedY < endY) {
				if (obj.blockStore[roundedX - startX][roundedY - startY][z1 - startZ].type == 0) {
					roundedZ = z1;
					drawCube(roundedX, roundedY, roundedZ, Block{ 1 }, 100, true);
				}
			}
		}
	}
}

