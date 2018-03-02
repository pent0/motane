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

#include <vector>
#include <glad/glad.h>

#include <graphics/type.h>
#include <utils/log.h>
#include <utils/type.h>

namespace motane {
	namespace graphics {
		//Contains a shader, for now lets use a GLSL shader
		//There is nothing important, yet no entry point
		class Shader {
			std::vector<char> buf;
			std::vector<char> buf2;

			RenderAPI api;

			u32 program;

		public:
			Shader(const char* nbuf, u32 size, const char* nbuf2, u32 size2, RenderAPI api = RenderAPI::OpenGL);

			bool compileShader();
			void use();

		};
	}
}