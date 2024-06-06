cmake_minimum_required(VERSION 3.10)
project(MarchingCubes)

# Find SYCL
#find_package(SYCL REQUIRED)

# Include directories
include_directories(include)

# Source files
set(SOURCES
	src/MarchingCubes.cpp
	src/Grid.cpp
	src/Isosurface.cpp
	src/SYCLUtils.cpp
	src/LookupTables.cpp
	main.cpp
)

# Executable
add_executable(MarchingCubes ${SOURCES})

# Link SYCL
#target_link_libraries(MarchingCubes SYCL::SYCL)
