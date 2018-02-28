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

#include <io/controller.h>

namespace motane {
	namespace io {
		std::vector<float> Controller::axesValue() const {
			std::vector<float> res;

			int ac = 0;
			const float *val = glfwGetJoystickAxes(index, &ac);

			if (val == nullptr) {
				return res;
			}

			res.resize(ac);

			memcpy(reinterpret_cast<void*>(&res[0]), val, ac * sizeof(float));

			return res;
		}

		Controller::Controller(const u16 index)
			: index(index) {
			int res = glfwJoystickPresent(index);

			if (res == GLFW_TRUE) {
				valid = true;
			}
			else {
				valid = false;
			}
		}

		u8 Controller::axesCount() {
			int ac = 0;
			glfwGetJoystickAxes(index, &ac);

			return static_cast<u8>(ac);
		}

		std::string Controller::name() const {
			const char *nm = glfwGetJoystickName(index);
			return nm;
		}

		math::vec2 Controller::getLeftAxis() const {
			auto axis = axesValue();

			return math::vec2(axis[GLFW_GAMEPAD_AXIS_LEFT_X], axis[GLFW_GAMEPAD_AXIS_LEFT_Y]);
		}

		math::vec2 Controller::getRightAxis() const {
			auto axis = axesValue();

			return math::vec2(axis[GLFW_GAMEPAD_AXIS_RIGHT_X], axis[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
		}

		math::vec2 Controller::getTriggerAxis() const {
			auto axis = axesValue();

			return math::vec2(axis[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER], axis[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
		}

		bool Controller::pressed(ButtonName name) const {
			int count = 0;
			const u8* state = glfwGetJoystickButtons(index, &count);

			return state[static_cast<u32>(name)] == GLFW_PRESS;
		}

		bool Controller::present() const {
			return valid;
		}

		Controller::operator bool() const {
			return present();
		}
	}
}