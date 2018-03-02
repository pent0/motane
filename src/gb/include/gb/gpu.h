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

#include <vector>

#include <gb/memory.h>
#include <graphics/framebuffer_soft.h>

namespace motane {
	namespace graphics {
		class Graphic;
	}
	
	namespace gb {
		enum {
			TILE_WH = 8,
			TOTAL_TILES = 384,
			SCREEN_WIDTH = 160,
			SCREEN_HEIGHT = 144,
			TWO_MAP_CAP = 512
		};

		class Memory;
		
		using Tile = graphics::FramebufferSoft;

		class GPU {
			std::vector<Tile>         tilesets;
			// Every GPU has access to the memory, isnt it (it's the GPU mem, but i grouped it :P)
			Memory &mem;

			graphics::FramebufferSoft framebuffer;
			graphics::Graphic &graphs;

			math::vec2 scroll;

		public:
			GPU() = default;
			GPU(const graphics::Graphic coreGraphic, Memory &mem);

			void updateTile(Address addr, u8 data) {
				u32 tile = (addr >> 4) & (TWO_MAP_CAP -1); // Find the index of the title by divide it by 8 and region it
				u32 y = (addr >> 1) & (TILE_WH - 1); // Find the row (just region it between 0 and 8)

				for (u8 x = 0; x < TILE_WH; x++) {
					u32 bi = 1 << (TILE_WH - 1 - x);

					u8 lb = mem.read<u8>(addr);
					u8 lbn = mem.read<u8>(addr + 1);

					tilesets[tile].write(math::vec2(y, x), lb & bi ? 1 : 0 + lbn & bi ? 2 : 0);
				}
			}

			void render() {

			}
		};
	}
}