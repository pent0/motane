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