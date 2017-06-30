#pragma once

#ifndef MAIN_H
#define MAIN_H

#include "Memory.h"
#include "cpu.h"
#include "display.h"
#include "keyboard.h"

class Main {
private:

	int clock_speed;

	void run();
	void setClock(int speed);

};

#endif