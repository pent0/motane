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

#include <utils/log.h>

#ifdef WIN32
#include <windows.h>
#include <processenv.h>
#include <shellapi.h>
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

#ifdef _MSC_VER
#include <spdlog/sinks/msvc_sink.h>
#endif

#ifdef WIN32
#include <spdlog/sinks/wincolor_sink.h>
#endif

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>
#include <spdlog/sinks/ansicolor_sink.h>

#include <iostream>
#include <codecvt>   
#include <locale>    

namespace motane {
std::shared_ptr<spdlog::logger> g_logger;

//Copy from Vita3k
void initLogging() {
		static constexpr bool LOG_MSVC_OUTPUT = true;
		std::vector<spdlog::sink_ptr> sinks;

	#ifdef WIN32
		sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
	#else
		sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>());
	#endif
		try
		{
			spdlog::filename_t s_cwd;

	#ifdef WIN32
			wchar_t buffer[MAX_PATH];
			GetModuleFileNameW(NULL, buffer, MAX_PATH);
			std::string::size_type pos = std::wstring(buffer).find_last_of(L"\\\\");
			std::wstring path = std::wstring(buffer).substr(0, pos);
			if (!path.empty()) {
				std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
				s_cwd = conv.to_bytes(path);
			}
	#else
			char buffer[512];
			char *path = getcwd(buffer, sizeof(buffer));
			if (path)
				s_cwd = path;
	#endif
			else
			{
				std::cerr << "failed to get working directory" << std::endl;
			}
			sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_mt>(s_cwd + "/Motane.log"));
		}
		catch (const spdlog::spdlog_ex& ex)
		{
			std::cerr << "File log initialization failed: " << ex.what() << std::endl;
		}

	#ifdef _MSC_VER
		if (LOG_MSVC_OUTPUT)
			sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_st>());
	#endif

		g_logger = std::make_shared<spdlog::logger>("MotaneLogger", begin(sinks), end(sinks));
		spdlog::register_logger(g_logger);

		spdlog::set_error_handler([](const std::string& msg)
		{
			std::cerr << "Spdlog error: " << msg << std::endl;
		});

		spdlog::set_pattern("[%H:%M:%S.%e] [%l] %v");

		spdlog::set_level(spdlog::level::trace);
		g_logger->flush_on(spdlog::level::debug);
	}
}