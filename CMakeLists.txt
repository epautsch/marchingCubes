cmake_minimum_required(VERSION 3.10)
project(marchingCubes)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/grid.cpp
    src/isosurface.cpp
)

# Include directories
include_directories(include)

# Find and include Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_grid tests/test_grid.cpp ${SOURCES})
add_executable(test_isosurface tests/test_isosurface.cpp ${SOURCES})

# Link Google Test libraries
target_link_libraries(test_grid ${GTEST_LIBRARIES} pthread)
target_link_libraries(test_isosurface ${GTEST_LIBRARIES} pthread)

enable_testing()
add_test(NAME GridTests COMMAND test_grid)