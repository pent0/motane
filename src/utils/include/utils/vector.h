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

#include <utils/type.h>

namespace motane {
	namespace math {
		struct vec2 {
			float x, y;

			vec2(const float x, const float y)
				: x(x), y(y) {}
		};

		struct vec3: public vec2 {
			float z;

			vec3(const float x, const float y, const float z)
				: vec2(x, y), z(z) {}
		};

		struct vec4 : public vec3 {
			float w;

			vec4(const float x, const float y, const float z, const float w)
				: vec3(x, y, z), w(w) {}
		};
	}
}