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

#include <spdlog/logger.h>
#include <memory>

namespace motane {
	extern std::shared_ptr<spdlog::logger> g_logger;

	void initLogging();
}

#define motane_log_trace(fmt, ...) g_logger->trace("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_log_debug(fmt, ...) g_logger->debug("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_log_info(fmt, ...) g_logger->info("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_log_warn(fmt, ...) g_logger->warn("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_log_error(fmt, ...) g_logger->error("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_log_critical(fmt, ...) g_logger->critical("[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)

#define motane_trace_if(flag, fmt, ...) g_logger->trace_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_debug_if(flag, fmt, ...) g_logger->debug_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_info_if(flag, fmt, ...) g_logger->info_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_warn_if(flag, fmt, ...) g_logger->warn_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_error_if(flag, fmt, ...) g_logger->error_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)
#define motane_critical_if(flag, fmt, ...) g_logger->critical_if(flag, "[ {:s} ]:    " fmt, __FUNCTION__, ## __VA_ARGS__)