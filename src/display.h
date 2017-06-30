#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
#define PIXELS_WIDTH 64
#define PIXELS_HEIGHT 32

#include <SDL.h>

class Display {

private:
	SDL_Event event;
	SDL_Surface* screenSurface;
	SDL_Surface* pixel_s;
	SDL_Window* window;
	SDL_Renderer* renderer;

	double last_time = 0;

	//SDL_Rect* pixel;

	uint8_t disp_mem[PIXELS_WIDTH][PIXELS_HEIGHT];

public:
	Display();
	int32_t scale;
	int events();
	void drawPixel(int x, int y, int colour);
	void render();
	void setPixel(int x, int y, uint8_t value);
	void initDisplay();
	void clear();
	void delay();

	uint8_t getPixel(int x, int y);
	SDL_Event* getEvent();
};

#endif