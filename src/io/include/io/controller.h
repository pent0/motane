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
#include <utils/vector.h>

#include <vector>

namespace motane {
	namespace io {
		enum class ButtonName {
			A = GLFW_GAMEPAD_BUTTON_A,
			B = GLFW_GAMEPAD_BUTTON_B,
			X = GLFW_GAMEPAD_BUTTON_X,
			Y = GLFW_GAMEPAD_BUTTON_Y,
			Cross = GLFW_GAMEPAD_BUTTON_CROSS,
			Circle = GLFW_GAMEPAD_BUTTON_CIRCLE,
			Triangle = GLFW_GAMEPAD_BUTTON_TRIANGLE,
			Square = GLFW_GAMEPAD_BUTTON_SQUARE,
			Start = GLFW_GAMEPAD_BUTTON_START,
			DPadUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,
			DPadDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
			DPadRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
			DPadLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
			LeftBumper = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		    RightBumper = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
			LeftThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
			RightThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB
		};

		class Controller {
			bool valid;
			u16  index; 

		protected:

			std::vector<float> axesValue() const;

		public:
			Controller(const u16 index);

			u8 axesCount();
			std::string name() const;

			math::vec2 getLeftAxis() const;
			math::vec2 getRightAxis() const;
			math::vec2 getTriggerAxis() const;

			bool pressed(ButtonName name) const;
			bool present() const;

			operator bool() const;
		};
	}
}