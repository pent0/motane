include_directories(include)
add_library(motanegb
     STATIC
     include/gb/register.h
	 include/gb/loader.h
     include/gb/memory.h
     include/gb/interpreter.h
     src/memory.cpp
	 src/loader.cpp)

target_link_libraries(motanegb motaneutils)