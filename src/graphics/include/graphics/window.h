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

#include <GLFW/glfw3.h>

#include <utils/type.h>
#include <memory>
#include <string>

namespace motane {
	namespace graphics {
		class Window {
			GLFWwindow* mainWindow;
			Window* linkWindow;

			u32 width, height, x, y;

			std::string title;
		public:
			Window() = default;
			Window(const std::string title, const u32 width, const u32 height,
				const u32 x, const u32 y, Window *linkAntWindow = nullptr);
		};
	}
}