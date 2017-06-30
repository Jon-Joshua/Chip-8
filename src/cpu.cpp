#include "cpu.h"
#include <Windows.h>
#include <bitset>
using namespace std;

CPU::CPU(Memory* m, Display* d, Keyboard* k) {
	mem = m;
	dis = d;
	key = k;

	sp = 0;
	pc = 0x200;

	dt, st = 0;
}

void CPU::updateTimers() {

	if (dt > 0) {
		dt--;
	}

	if (st > 0) {
		st--;
	}
}

void CPU::run(int cycles) {

	for (int i = 0; i <	cycles; i++) {

		opcode = (mem->getByte(pc) << 8) | (mem->getByte(pc + 1));
		pc += 2;

		uint16_t addr = opcode & 0xfff;
		uint8_t kk = opcode & 0xff;
		uint8_t nibble = opcode & 0xf;

		uint8_t x = (opcode >> 8) & 0xf;
		uint8_t y = (opcode >> 4) & 0xf;

		int* key_map = key->getKeyMap();

		cout << hex << pc - 2;
		cout << " - ";
		cout << hex << opcode << endl;

		switch (opcode & 0xf000) {

		case 0x0000:

			switch (opcode & 0x00ff) {

			case 0x00e0: // Clear the display.
				dis->clear();
				break;

			case 0x00ee: // Return from a subroutine.
				sp--;
				pc = stack[sp];
				break;
			}
			break;

		case 0x1000: // Jump to location nnn.
			pc = addr;
			break;

		case 0x2000: //2nnn - CALL addr
			stack[sp++] = pc;
			pc = addr;
			break;

		case 0x3000: // Skip next instruction if Vx = kk.
			if (v[x] == kk) {
				pc += 2;
			}
			break;

		case 0x4000: // Skip next instruction if Vx != kk.
			if (v[x] != kk) {
				pc += 2;
			}
			break;

		case 0x5000: // Skip next instruction if Vx = Vy.
			if (v[x] == v[y]) {
				pc += 2;
			}
			break;

		case 0x6000: // 6xkk - LD Vx, byte
			v[x] = kk;
			break;

		case 0x7000: // 7xkk - ADD Vx, byte
			v[x] = v[x] + kk;
			break;

		case 0x8000:

			switch (opcode & 0x000f) {
			case 0x0000: // Stores the value of register Vy in register Vx.
				v[x] = v[y];
				break;

			case 0x0001: // Set Vx = Vx OR Vy.
				v[x] = v[x] | v[y];
				break;

			case 0x0002: // Set Vx = Vx AND Vy.
				v[x] = v[x] & v[y];
				break;

			case 0x0003: // Set Vx = Vx XOR Vy.
				v[x] = v[x] ^ v[y];
				break;

			case 0x0004: //  Set Vx = Vx + Vy, set VF = carry.
				v[x] += v[y];
				v[0xf] = (v[x] + v[y]) > 0xff;
				break;

			case 0x0005: // Set Vx = Vx - Vy, set VF = NOT borrow.
				v[0xf] = v[x] >= v[y];
				v[x] = v[x] - v[y];
				break;

			case 0x0006: // Set Vx = Vx SHR 1. Need to check alternative function.
				v[x] = v[x] & 0x01;
				break;

			case 0x0007: // Set Vx = Vy - Vx, set VF = NOT borrow.
				v[0xf] = v[y] >= v[x];
				v[x] = v[y] - v[x];
				break;

			case 0x000E: // Set Vx = Vx SHL 1.
				v[x] = v[x] & 0x01;
				
				break;
			}

			break;

		case 0x9000: // Skip next instruction if Vx != Vy.
			if (v[x] != v[y]) {
				pc += 2;
			}
			break;

		case 0xA000: // Annn - LD I, addr
			I = addr;
			break;

		case 0xB000: // Jump to location nnn + V0.
			pc = addr + v[0];
			break;

		case 0xC000: // Set Vx = random byte AND kk.
			v[x] = (rand() % 0xFF) & kk;
			break;

		case 0xD000:

			v[0xf] = 0;

			for (int i = 0; i < nibble; i++) {
				uint8_t value = mem->getByte(I + i);
				for (int j = 0; j < 8; j++) {

					int pixel_x = (v[x] + j) % PIXELS_WIDTH;
					int pixel_y = (v[y] + i) % PIXELS_HEIGHT;

					/* Set hit collision
					/* (v[f] OR curr_pixel) AND new_pixel
					*/
					v[0xf] |= dis->getPixel(pixel_x, pixel_y) & ((value >> 7 - j) & 1);

					dis->setPixel(pixel_x, pixel_y, (value >> 7 - j) & 1);
				}
			}

			draw_cycle = 1;

			break;

		case 0xE000:

			switch (opcode & 0x00ff) {

				case 0x009e: // Skip next instruction if key with the value of Vx is pressed.

					if (key->getKeyDown(v[x])) {
						pc += 2;
					}
					break;

				case 0x00a1: // Skip next instruction if key with the value of Vx is not pressed.

					if (!key->getKeyDown(v[x])) {
						pc += 2;
					}

					break;
			}
			break;

		case 0xF000:

			switch (opcode & 0x00FF) {

			case 0x0007: // Set Vx = delay timer value.
				v[x] = dt;
				break;

			case 0x000A: // Wait for a key press, store the value of the key in Vx.

				pc -= 2;

				for (int x = 0; x < 16; x++) {

					if (key->getKeyDown(x)) {
						v[x] = x;
						pc += 2;
					}

				}

				break;

			case 0x0015: // Set delay timer = Vx.
				dt = v[x];
				break;

			case 0x0018: // Set sound timer = Vx.
				st = v[x];
				break;

			case 0x001e: // Set I = I + Vx.
				I += v[x];
				break;

			case 0x0029:
				I = v[x] * 5;
				break;

			case 0x0033: // Store BCD representation of Vx in memory locations I, I+1, and I+2.
				mem->setByte(I, v[x] / 100);
				mem->setByte(I + 1, (v[x] / 10) % 10);
				mem->setByte(I + 2, (v[x] % 100) % 10);
				break;

			case 0x0055: // Store registers V0 through Vx in memory starting at location I.
				for (int i = 0; i <= x; i++) {
					mem->setByte(I + i, v[x]);
				}
				break;

			case 0x0065: // Read registers V0 through Vx from memory starting at location I.
				for (int i = 0; i <= x; i++) {
					v[i] = mem->getByte(I + i);
					//printf("Setting V" + i + mem->getByte(I + i));
				}
				break;
			}
			break;

		default:
			cout << hex << opcode << endl;
			break;

		}
	}
}