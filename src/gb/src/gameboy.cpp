#include <gb/gameboy.h>

#include <fstream>
#include <sstream>

#include <thread>

namespace motane {
	namespace gb {
		Gameboy::Gameboy(const GameboyCPUType type) :
			type(type), ex1(mem, reg, clock), state(GameboyState::Hold) {}

		void Gameboy::init(const char* romPath) {
			rom = load(romPath);
			std::ifstream file(romPath);
			std::stringstream strstream;

			strstream << file.rdbuf();

			mem = fillMemWithRom(strstream.str().data(), rom.romSize);
		}

		void Gameboy::hold() {
			std::lock_guard<std::mutex> guard(mut);
			state = GameboyState::Hold;
		}

		void Gameboy::stop() {
			std::lock_guard<std::mutex> guard(mut);
			state = GameboyState::Stop;
		}

		void Gameboy::play() {
			if (state == GameboyState::Run || state == GameboyState::Stop) {
				motane_log_warn("Stop calling playing. It's already running, or stopped.");
				return;
			}

			//Run the interpreter in another thread, so we could easily stop it form outside
			std::thread play_thread([this]() {
				std::lock_guard<std::mutex> guard(mut);
				state = GameboyState::Run;

				while (state == GameboyState::Run) {
					if (type == GameboyCPUType::Interpreter) {
						//Nothing uses the memory and register rather than the fetch function
						bool res = ex1.fetch();

						if (!res) {
							std::lock_guard<std::mutex> guard2(mut);
							state = GameboyState::Stop;
						}
					}
				}
			});

			play_thread.join();
		}
	}
}