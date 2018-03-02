include_directories(include)
add_library(motanegraphics
     STATIC
     include/graphics/ogl/framebuffer.h
	 include/graphics/type.h
	 include/graphics/window.h
	 include/graphics/framebuffer_soft.h
	 include/graphics/graphic.h
	 include/graphics/shader.h
     src/ogl/framebuffer.cpp
	 src/window.cpp
	 src/shader.cpp
	 src/graphic.cpp)

target_link_libraries(motanegraphics glfw opengl32)