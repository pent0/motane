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

#include <graphics/shader.h>

namespace motane {
	namespace graphics {
		Shader::Shader(const char* nbuf, u32 size, const char* nbuf2, u32 size2, RenderAPI api)
			: api(api) {
			buf.resize(size);
			memcpy(&buf[0], nbuf, size);

			buf2.resize(size);
			memcpy(&buf2[0], nbuf2, size2);
		}

		bool Shader::compileShader() {
			u32 vertexShaderPointer;
			u32 fragmentShaderPointer;

			if (api == RenderAPI::OpenGL) {
				vertexShaderPointer = glCreateShader(GL_VERTEX_SHADER);
				fragmentShaderPointer = glCreateShader(GL_FRAGMENT_SHADER);
			}

			const char* dat = buf.data();
			const char* dat2 = buf.data();

			glShaderSource(vertexShaderPointer, 1, &dat, nullptr);
			glCompileShader(vertexShaderPointer);

			glShaderSource(fragmentShaderPointer, 1, &dat2, nullptr);
			glCompileShader(fragmentShaderPointer);

			GLint res = 1;
			GLint res2 = 1;

			GLchar infoLog[512];

			glGetShaderiv(vertexShaderPointer, GL_COMPILE_STATUS, &res);
			glGetShaderiv(fragmentShaderPointer, GL_COMPILE_STATUS, &res2);

			if (!res)
			{
				glGetShaderInfoLog(res, 512, NULL, infoLog);
				motane_log_error("Error in vertex shader compilation: ", infoLog);
			}

			if (!res2) {
				glGetShaderInfoLog(res2, 512, NULL, infoLog);
				motane_log_error("Error in fragment shader compilation: ", infoLog);
			}

			if (!res || !res2) {
				return false;
			}

			program = glCreateProgram();

			glAttachShader(program, vertexShaderPointer);
			glAttachShader(program, fragmentShaderPointer);

			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &res);

			if (!res) {
				glGetProgramInfoLog(res, 512, NULL, infoLog);
				motane_log_error("Error in linking shader program: ", infoLog);

				return false;
			}

			return true;
		}

		void Shader::use() {
			glUseProgram(program);
		}

	}
}