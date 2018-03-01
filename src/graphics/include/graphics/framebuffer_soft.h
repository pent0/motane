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

#include <utils/type.h>
#include <utils/vector.h>

namespace motane {
	namespace graphics {
		class FramebufferSoft {
			std::vector<std::vector<char>> buf;

		public:
			FramebufferSoft() = default;
			FramebufferSoft(const char** data, u32 sizeWidth, u32 sizeHeight) {
				buf.resize(sizeWidth);

				for (u32 i = 0; i < sizeWidth; i++) {
					memcpy(&buf[i][0], data[i], sizeHeight);
				}
			}

			const char* operator [](u32 index) const {
				return buf[index].data();
			}

			char read(math::vec2 pos) const {
				return buf[pos.x][pos.y];
			}

			void write(math::vec2 pos, const char data) {
				buf[pos.x][pos.y] = data;
			}
		};
	}
}