#include <string>
#include <iostream>

#include <SDL.h>
#include <stdio.h>
#include <Windows.h>
#include "memory.h"
#include "keyboard.h"
#include "display.h"
#include "cpu.h"

int main(int argc, char *args[]) {

	Display dis = Display();
	Memory mem = Memory();
	Keyboard key = Keyboard();
	CPU cpu = CPU(&mem, &dis, &key);

	char* path = "C:\\Users\\Jon\\Documents\\visual studio 2015\\Projects\\WindowsFormsApplication1\\WindowsFormsApplication1\\Roms\\PONG";

	if (mem.loadRom(path)) {
		cout << "Rom loaded into memory" << endl;
	}

	int clock_speed = 840;
	int old_clock_speed = clock_speed;

	int running = 1;

	cout << clock_speed / 60 << endl;

	while (running) {

		key.event(dis.getEvent());

		if (key.restart) {
			mem = Memory();
			mem.loadRom(path);
			cpu = CPU(&mem, &dis, &key);
			dis.clear();
			Sleep(1);
		}

		if (!key.paused) {
			if (cpu.draw_cycle) {
				cpu.draw_cycle = 0;
				dis.render();
				dis.delay();
			}
			cpu.run(clock_speed / 60);
			cpu.updateTimers();
		} else {
			Sleep(1);
		}
		Sleep(100);
	}
	return 0;
}