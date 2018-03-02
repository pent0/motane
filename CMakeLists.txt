cmake_minimum_required(VERSION 3.8)
project(motane)

include_directories(spdlog/include)
include_directories(glfw/include)
include_directories(glad/include)

add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_subdirectory(src)