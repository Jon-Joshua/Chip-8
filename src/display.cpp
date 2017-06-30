#include "display.h"
#include <string>
#include <iostream>



using namespace std;

Display::Display() {

	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			disp_mem[x][y] = 0;
		}
	}

	initDisplay();
}

void Display::initDisplay() {

	scale = 10;

	const int SCREEN_WIDTH = PIXELS_WIDTH * scale;
	const int SCREEN_HEIGHT = PIXELS_HEIGHT * scale;


	//The window we'll be rendering to
	window = NULL;
	//The surface contained by the window
	screenSurface = NULL;

	SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else { //Create window
		window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else { //Get window surface
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_RenderClear(renderer);

			// Wait for 5 sec
			SDL_Delay(2000);
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_UpdateWindowSurface(window);
}

void Display::drawPixel(int x, int y, int colour) {

	SDL_Rect pixel;

	pixel.x = x * scale;
	pixel.y = y * scale;
	pixel.h = scale;
	pixel.w = scale;

	if (colour == 1) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
	} else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	// Render rect
	SDL_RenderFillRect(renderer, &pixel);
}

void Display::setPixel(int x, int y, uint8_t value) {
	disp_mem[x][y] = disp_mem[x][y] ^ value;
}

uint8_t Display::getPixel(int x, int y) {
	return disp_mem[x][y];
}

SDL_Event* Display::getEvent() {
	return &event;
}

void Display::render() {

	for (int x = 0; x < PIXELS_WIDTH; x++) {
		for (int y = 0; y < PIXELS_HEIGHT; y++) {
			drawPixel(x, y, disp_mem[x][y]);
		}
	}

	// Render the rect to the screen
	SDL_RenderPresent(renderer);

	// Code from https://github.com/AlfonsoJLuna/chip8swemu

	//double current_time = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
	//double busy_time = current_time - last_time;
	//if ((busy_time * 1000) < (1000 / 60))
	//	SDL_Delay(1000 / 60 - busy_time * 1000);
	//last_time = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();

	SDL_GL_SwapWindow(window);
}

void Display::delay() {

	// Code from https://github.com/AlfonsoJLuna/chip8swemu

	double current_time = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();
	double busy_time = current_time - last_time;
	if ((busy_time * 1000) < (1000 / 60))
		SDL_Delay(1000 / 60 - busy_time * 1000);
	last_time = SDL_GetPerformanceCounter() / SDL_GetPerformanceFrequency();

}

void Display::clear() {

	memset(disp_mem, 0, sizeof(disp_mem));

	//for (int x = 0; x < PIXELS_WIDTH; x++) {
	//	for (int y = 0; y < PIXELS_HEIGHT; y++) {
	//		disp_mem[x][y] = 0;
	//	}
	//}
}

int Display::events() {
	return 0;

}