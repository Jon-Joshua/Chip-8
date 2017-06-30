#pragma once

#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "display.h"
#include "keyboard.h"
#include <iostream>

class CPU {

private:
	Memory* mem;
	Display* dis;
	Keyboard* key;

	uint8_t v[16];

	uint16_t opcode;
	uint16_t pc;
	uint8_t sp;

	uint16_t stack[16];
	uint16_t I;

	uint8_t dt;
	uint8_t st;

public:
	CPU(Memory* m, Display* d, Keyboard* k);
	void run(int cycles);
	void updateTimers();
	int draw_cycle;

};

#endif
