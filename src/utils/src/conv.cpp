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

#include <utils/conv.h>

namespace motane {
	s16 make_s16(s8 h, s8 l) {
		return h << 8 + l;
	}

	std::pair<s8, s8> extract_s16(s16 hl) {
		return std::make_pair((hl >> 8) & 255, hl & 255);
	}

	u16 make_u16(u8 h, u8 l) {
		return h << 8 + l;
	}

	std::pair<u8, u8> extract_u16(u16 hl) {
		return std::make_pair((hl >> 8) & 255, hl & 255);
	}
}