#include <gb/loader.h>

int main(int argc, char** argv) {
	motane::gb::GameboyRom rom = motane::gb::load("D:\\tetris.gb");

	return 0;
}