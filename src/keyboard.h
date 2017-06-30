#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL.h>
#include <string>
#include <iostream>

using namespace std;

class Keyboard {

private:
	int key_map[16];

public:
	int paused = 0;
	int slow = 0;
	int restart = 0;

	Keyboard();
	int event(SDL_Event* event);

	int* getKeyMap();
	char getKeyPressed();
	int getKeyDown(int key);
};

#endif // !KEYBOARD_
