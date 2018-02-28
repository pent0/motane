include_directories(include)
add_library(motanegraphics
     STATIC
     include/graphics/ogl/framebuffer.h
	 include/graphics/type.h
	 include/graphics/window.h
     src/ogl/framebuffer.cpp)

target_link_libraries(motanegraphics glfw)