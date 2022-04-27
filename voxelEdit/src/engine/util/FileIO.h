#pragma once
#include <fstream>
#include "../types/Object.h"
#include "../../Globals.h"

void getObjectFromFile(int index, std::string name, Object& obj, int& xSize, int& ySize, int& zSize);
void getObjectFromFile(int index, std::string name, Object& obj);
int writeObjectToFile(std::string name, Object obj);

void getObjectFromFile(int index, std::string name, Object& obj, int& xSize, int& ySize, int& zSize) {
	//read object from .oof binary file
	obj.init = true;

	std::ifstream fin;
	fin.open(name + ".oof", std::ios::binary | std::ios::in);

	char ch;
	fin.read(&ch, 1); //byte 1 is size in x direction
	xSize = ch;
	fin.read(&ch, 1); //byte 2 is size in y direction
	ySize = ch;
	fin.read(&ch, 1); //byte 3 is size in z direction
	zSize = ch;
	fin.read(&ch, 1); //byte 4 is size of each block in object
	obj.blockSize = ch;
	short type;

	char* sh = new char[2];

	//bytes 5 - ??? are the actual blocks in the object
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				//each block type is a short (2 bytes) so the separate bytes are bit shifted into a variable
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
	//read object from .oof binary file
	obj.init = true;

	int xSize, ySize, zSize;

	std::ifstream fin;
	fin.open(name, std::ios::binary | std::ios::in);

	char ch;
	fin.read(&ch, 1); //byte 1 is size in x direction
	xSize = ch;
	fin.read(&ch, 1); //byte 2 is size in y direction
	ySize = ch;
	fin.read(&ch, 1); //byte 3 is size in z direction
	zSize = ch;
	fin.read(&ch, 1); //byte 4 is size of each block in object
	obj.blockSize = ch;
	short type;

	char* sh = new char[2];

	//bytes 5 - ??? are the actual blocks in the object
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				//each block type is a short (2 bytes) so the separate bytes are bit shifted into a variable
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
	fout.open(name + ".oof", std::ios::out | std::ios::binary);

	byte xSize = sizeof(obj.blockStore) / sizeof(obj.blockStore[0]);				//size of object in x direction
	byte ySize = sizeof(obj.blockStore[0]) / sizeof(obj.blockStore[0][0]);			//size of object in y direction
	byte zSize = sizeof(obj.blockStore[0][0]) / sizeof(obj.blockStore[0][0][0]);	//size of object in z direction

	fout << xSize;
	fout << ySize;
	fout << zSize;
	fout << obj.blockSize;

	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			for (int z = 0; z < zSize; z++) {
				//bit shift to convert short into two bytes
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