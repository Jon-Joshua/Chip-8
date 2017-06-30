#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#define MAX_MEMORY 4096

#define _CRT_SECURE_NO_DEPRECATE

#include <string>

class Memory {

private:
	unsigned char mem[MAX_MEMORY];

public:
	Memory();
	unsigned char getByte(int addr);
	void setByte(int addr, uint8_t data);
	void init();

	int loadRom(char* path);
};

#endif