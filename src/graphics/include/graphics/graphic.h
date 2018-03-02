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

#include <glad/glad.h>

#include <graphics/type.h>
#include <graphics/window.h>

#include <functional>
#include <map>

namespace motane {
	namespace graphics {
		class Window;
		
		class Graphic {
			std::map<GLFWwindow*, Window> windows;
			RenderAPI api;

		protected:

			void onWindowSizeChange(GLFWwindow *window, int newSizeX, int newSizeY);
			void onWindowPosChange(GLFWwindow *window, int newPosX, int newPosY);

		public:
			void init();
			Graphic() = default;
			Graphic(const std::string title, const math::vec2 size, const math::vec2 pos, bool showMouse = false,
				bool resizeable = false, u8 splitManu = 0, RenderAPI api = RenderAPI::OpenGL);
		};
	}
}