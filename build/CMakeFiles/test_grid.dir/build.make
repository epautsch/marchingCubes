# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jorgevelez/Desktop/marchingCubes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jorgevelez/Desktop/marchingCubes/build

# Include any dependencies generated for this target.
include CMakeFiles/test_grid.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_grid.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_grid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_grid.dir/flags.make

CMakeFiles/test_grid.dir/tests/test_grid.cpp.o: CMakeFiles/test_grid.dir/flags.make
CMakeFiles/test_grid.dir/tests/test_grid.cpp.o: /Users/jorgevelez/Desktop/marchingCubes/tests/test_grid.cpp
CMakeFiles/test_grid.dir/tests/test_grid.cpp.o: CMakeFiles/test_grid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorgevelez/Desktop/marchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_grid.dir/tests/test_grid.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_grid.dir/tests/test_grid.cpp.o -MF CMakeFiles/test_grid.dir/tests/test_grid.cpp.o.d -o CMakeFiles/test_grid.dir/tests/test_grid.cpp.o -c /Users/jorgevelez/Desktop/marchingCubes/tests/test_grid.cpp

CMakeFiles/test_grid.dir/tests/test_grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_grid.dir/tests/test_grid.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorgevelez/Desktop/marchingCubes/tests/test_grid.cpp > CMakeFiles/test_grid.dir/tests/test_grid.cpp.i

CMakeFiles/test_grid.dir/tests/test_grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_grid.dir/tests/test_grid.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorgevelez/Desktop/marchingCubes/tests/test_grid.cpp -o CMakeFiles/test_grid.dir/tests/test_grid.cpp.s

CMakeFiles/test_grid.dir/src/grid.cpp.o: CMakeFiles/test_grid.dir/flags.make
CMakeFiles/test_grid.dir/src/grid.cpp.o: /Users/jorgevelez/Desktop/marchingCubes/src/grid.cpp
CMakeFiles/test_grid.dir/src/grid.cpp.o: CMakeFiles/test_grid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorgevelez/Desktop/marchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_grid.dir/src/grid.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_grid.dir/src/grid.cpp.o -MF CMakeFiles/test_grid.dir/src/grid.cpp.o.d -o CMakeFiles/test_grid.dir/src/grid.cpp.o -c /Users/jorgevelez/Desktop/marchingCubes/src/grid.cpp

CMakeFiles/test_grid.dir/src/grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_grid.dir/src/grid.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorgevelez/Desktop/marchingCubes/src/grid.cpp > CMakeFiles/test_grid.dir/src/grid.cpp.i

CMakeFiles/test_grid.dir/src/grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_grid.dir/src/grid.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorgevelez/Desktop/marchingCubes/src/grid.cpp -o CMakeFiles/test_grid.dir/src/grid.cpp.s

CMakeFiles/test_grid.dir/src/isosurface.cpp.o: CMakeFiles/test_grid.dir/flags.make
CMakeFiles/test_grid.dir/src/isosurface.cpp.o: /Users/jorgevelez/Desktop/marchingCubes/src/isosurface.cpp
CMakeFiles/test_grid.dir/src/isosurface.cpp.o: CMakeFiles/test_grid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jorgevelez/Desktop/marchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_grid.dir/src/isosurface.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_grid.dir/src/isosurface.cpp.o -MF CMakeFiles/test_grid.dir/src/isosurface.cpp.o.d -o CMakeFiles/test_grid.dir/src/isosurface.cpp.o -c /Users/jorgevelez/Desktop/marchingCubes/src/isosurface.cpp

CMakeFiles/test_grid.dir/src/isosurface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_grid.dir/src/isosurface.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jorgevelez/Desktop/marchingCubes/src/isosurface.cpp > CMakeFiles/test_grid.dir/src/isosurface.cpp.i

CMakeFiles/test_grid.dir/src/isosurface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_grid.dir/src/isosurface.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jorgevelez/Desktop/marchingCubes/src/isosurface.cpp -o CMakeFiles/test_grid.dir/src/isosurface.cpp.s

# Object files for target test_grid
test_grid_OBJECTS = \
"CMakeFiles/test_grid.dir/tests/test_grid.cpp.o" \
"CMakeFiles/test_grid.dir/src/grid.cpp.o" \
"CMakeFiles/test_grid.dir/src/isosurface.cpp.o"

# External object files for target test_grid
test_grid_EXTERNAL_OBJECTS =

test_grid: CMakeFiles/test_grid.dir/tests/test_grid.cpp.o
test_grid: CMakeFiles/test_grid.dir/src/grid.cpp.o
test_grid: CMakeFiles/test_grid.dir/src/isosurface.cpp.o
test_grid: CMakeFiles/test_grid.dir/build.make
test_grid: /usr/local/lib/libgtest.a
test_grid: CMakeFiles/test_grid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jorgevelez/Desktop/marchingCubes/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_grid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_grid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_grid.dir/build: test_grid
.PHONY : CMakeFiles/test_grid.dir/build

CMakeFiles/test_grid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_grid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_grid.dir/clean

CMakeFiles/test_grid.dir/depend:
	cd /Users/jorgevelez/Desktop/marchingCubes/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jorgevelez/Desktop/marchingCubes /Users/jorgevelez/Desktop/marchingCubes /Users/jorgevelez/Desktop/marchingCubes/build /Users/jorgevelez/Desktop/marchingCubes/build /Users/jorgevelez/Desktop/marchingCubes/build/CMakeFiles/test_grid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_grid.dir/depend
