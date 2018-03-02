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

#include <gb/gameboy.h>

#include <fstream>
#include <sstream>

#include <thread>

namespace motane {
	namespace gb {
		Gameboy::Gameboy(const CPUType type) :
			type(type), ex1(mem, reg, clock), state(State::Hold) {}

		void Gameboy::init(const char* romPath) {
			rom = load(romPath);
			
			std::vector<char> data(rom.romSize);
			std::ifstream file(romPath, std::ios::binary);

			file.read(&data[0], rom.romSize);

			mem = fillMemWithRom(data.data(), rom.romSize);
		}

		void Gameboy::hold() {
			std::lock_guard<std::mutex> guard(mut);
			state = State::Hold;
		}

		void Gameboy::stop() {
			std::lock_guard<std::mutex> guard(mut);
			state = State::Stop;
		}

		void Gameboy::play() {
			if (state == State::Run || state == State::Stop) {
				motane_log_warn("Stop calling playing. It's already running, or stopped.");
				return;
			}

			//Run the interpreter in another thread, so we could easily stop it form outside
			std::thread play_thread([this]() {
				std::lock_guard<std::mutex> guard(mut);
				state = State::Run;

				while (state == State::Run) {
					if (type == CPUType::Interpreter) {
						//Nothing uses the memory and register rather than the fetch function
						bool res = ex1.fetch();

						if (!res) {
							std::lock_guard<std::mutex> guard2(mut);
							state = State::Stop;
						}
					}
				}
			});

			play_thread.join();
		}
	}
}