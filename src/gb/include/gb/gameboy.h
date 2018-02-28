#pragma once

#include <gb/loader.h>
#include <gb/interpreter.h>
#include <gb/memory.h>
#include <gb/register.h>

#include <utils/log.h>

#include <mutex>

namespace motane {
	namespace gb {
		enum class GameboyCPUType {
			Interpreter = 0,
			DynarecLLVM = 1
		};

		enum class GameboyState {
			Run = 0,
			Hold = 1,
			Stop = 2
		};

		class Gameboy {
			Memory mem;
			Registers reg;
			Clock clock;

			Interpreter ex1;
			
			GameboyCPUType type;
			GameboyRom     rom;
			GameboyState   state;

			std::mutex     mut;
		public:
			Gameboy(const GameboyCPUType type);
			void init(const char* romPath);
			void hold();
			void stop();
			void play();
		};
	}
}