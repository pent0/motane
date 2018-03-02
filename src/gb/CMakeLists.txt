include_directories(include)
add_library(motanegb
     STATIC
     include/gb/register.h
	 include/gb/loader.h
     include/gb/memory.h
     include/gb/interpreter.h
	 include/gb/gameboy.h
	 include/gb/gpu.h
     src/memory.cpp
	 src/loader.cpp
	 src/gameboy.cpp
	 src/gpu.cpp)

target_link_libraries(motanegb motaneutils motanegraphics)