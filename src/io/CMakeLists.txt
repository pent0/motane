include_directories(include)
add_library(motaneio
     STATIC
     include/io/controller.h
     src/controller.cpp)

target_link_libraries(motaneio glfw)