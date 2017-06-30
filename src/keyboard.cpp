#include "keyboard.h"

Keyboard::Keyboard() {
	memset(key_map, 0, sizeof(key_map));
}

int* Keyboard::getKeyMap() {
	return key_map;
}

char Keyboard::getKeyPressed() {

	for (int x = 0; x < sizeof(key_map); x++) {
		if (key_map[x] == 1) {
			return key_map[x];
		}
	}
}

int Keyboard::getKeyDown(int key) {
	return key_map[key];
}

int Keyboard::event(SDL_Event* event)
{
	SDL_Event event_ = *event;

	SDL_PollEvent(&event_);

	switch (event_.type) {
	case SDL_QUIT:
		printf("Closing window.");
		return 0;
		break;

	case SDL_KEYDOWN:
		switch (event_.key.keysym.sym) {
			case SDLK_1:
				key_map[1] = 1;
				break;
			case SDLK_2:
				key_map[2] = 1;
				break;
			case SDLK_3:
				key_map[3] = 1;
				break;
			case SDLK_4:
				key_map[0xc] = 1;
				break;
			case SDLK_q:
				key_map[4] = 1;
				break;
			case SDLK_w:
				key_map[5] = 1;
				break;
			case SDLK_e:
				key_map[6] = 1;
				break;
			case SDLK_r:
				key_map[0xd] = 1;
				break;
			case SDLK_a:
				key_map[7] = 1;
				break;
			case SDLK_s:
				key_map[8] = 1;
				break;
			case SDLK_d:
				key_map[9] = 1;
				break;
			case SDLK_f:
				key_map[0xe] = 1;
				break;
			case SDLK_z:
				key_map[0xa] = 1;
				break;
			case SDLK_x:
				key_map[0] = 1;
				break;
			case SDLK_c:
				key_map[0xb] = 1;
				break;
			case SDLK_v:
				key_map[0xf] = 1;
				break;
			case SDLK_SPACE:
				if (paused) {
					paused = 0;
				} else {
					paused = 1;
				}
				break;
			case SDLK_LSHIFT:
				slow = 1;
				break;
			case SDLK_RETURN:
				restart = 1;
				break;
		}
		break;

	case SDL_KEYUP:
		switch (event_.key.keysym.sym) {
			case SDLK_1:
				key_map[1] = 0;
				break;
			case SDLK_2:
				key_map[2] = 0;
				break;
			case SDLK_3:
				key_map[3] = 0;
				break;
			case SDLK_4:
				key_map[0xc] = 0;
				break;
			case SDLK_q:
				key_map[4] = 0;
				break;
			case SDLK_w:
				key_map[5] = 0;
				break;
			case SDLK_e:
				key_map[6] = 0;
				break;
			case SDLK_r:
				key_map[0xd] = 0;
				break;
			case SDLK_a:
				key_map[7] = 0;
				break;
			case SDLK_s:
				key_map[8] = 0;
				break;
			case SDLK_d:
				key_map[9] = 0;
				break;
			case SDLK_f:
				key_map[0xe] = 0;
				break;
			case SDLK_z:
				key_map[0xa] = 0;
				break;
			case SDLK_x:
				key_map[0] = 0;
				break;
			case SDLK_c:
				key_map[0xb] = 0;
				break;
			case SDLK_v:
				key_map[0xf] = 0;
				break;
			case SDLK_LSHIFT:
				slow = 0;
				break;
			case SDLK_RETURN:
				restart = 0;
				break;
		}
		break;
	}
	return 1;
}
