add_subdirectory(/usr/src/gtest			# this line link external src and build to 
                 ${PROJECT_BINARY_DIR}/gtest)	# project build directory
include(CTest)
