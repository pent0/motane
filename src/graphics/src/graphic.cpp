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

#include <graphics/graphic.h>

#include <cassert>

namespace motane {
	namespace graphics {

		void Graphic::onWindowSizeChange(GLFWwindow *window, int newSizeX, int newSizeY) {
			auto ite = windows.find(window);

			(*ite).second.width(newSizeX);
			(*ite).second.height(newSizeY);
		}

		void Graphic::onWindowPosChange(GLFWwindow *window, int newPosX, int newPosY) {
			auto ite = windows.find(window);

			(*ite).second.pos(math::vec2(newPosX, newPosY));
		}

		void Graphic::init() {
			auto res1 = glfwInit();
			auto res2 = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

			assert(res1 && res2);
		}

		Graphic::Graphic(const std::string title, const math::vec2 size, const math::vec2 pos, bool showMouse,
			bool resizeable, u8 splitManu, RenderAPI api)
		{
			init();

			std::function<void(GLFWwindow*, int, int)> poscallFunc =
				std::bind(&Graphic::onWindowPosChange, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

			decltype(poscallFunc) sizecallFunc =
				std::bind(&Graphic::onWindowSizeChange, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

			auto newSizeX = size.x / (splitManu + 1);
			auto newSizeY = size.y / (splitManu + 1);

			Window win(title, newSizeX, newSizeY
				, pos.x, pos.y, nullptr, api, resizeable, showMouse);

			glfwSetWindowPosCallback(win.getNativeHandle(), *poscallFunc.target<GLFWwindowposfun>());
			glfwSetWindowSizeCallback(win.getNativeHandle(), *sizecallFunc.target<GLFWwindowsizefun>());

			auto res = windows.emplace(win.getNativeHandle(), std::move(win));

			if (splitManu) {
				auto windowPair = res;

				for (u8 i = 0; i < splitManu; i++) {
					Window win2(title, newSizeX, newSizeY
						, pos.x, pos.y, &((*windowPair.first).second), api, resizeable, showMouse);

					windowPair = windows.emplace(win2.getNativeHandle(), std::move(win2));

					glfwSetWindowPosCallback(win2.getNativeHandle(), *poscallFunc.target<GLFWwindowposfun>());
					glfwSetWindowSizeCallback(win2.getNativeHandle(), *sizecallFunc.target<GLFWwindowsizefun>());
				}
			}

		}

	}
}