#include <gb/gameboy.h>

using namespace motane;

int main(int argc, char** argv) {
	motane::initLogging();

	if (argc <= 1) {
		motane_log_critical("No input file.");
		return 0;
	}

	motane::gb::Gameboy gb(motane::gb::GameboyCPUType::Interpreter);
	gb.init(argv[argc-1]);

	gb.play();

	return 0;
}