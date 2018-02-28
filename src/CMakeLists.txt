include_directories(utils/include)
include_directories(gb/include)

add_subdirectory(gb)
add_subdirectory(utils)
add_subdirectory(io)

add_executable(motane main.cpp)
target_link_libraries(motane motanegb)