/*
	Motane
	Copyright (C) 2018 Do Trong Thu

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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