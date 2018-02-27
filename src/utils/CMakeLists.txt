include_directories(include)
add_library(motaneutils
     STATIC
     include/utils/log.h
	 include/utils/decl.h
	 include/utils/conv.h
	 include/utils/type.h
     src/conv.cpp)