# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cezary/CLionProjects/pw3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cezary/CLionProjects/pw3

# Include any dependencies generated for this target.
include src/tests/CMakeFiles/sandArrangementTest.dir/depend.make

# Include the progress variables for this target.
include src/tests/CMakeFiles/sandArrangementTest.dir/progress.make

# Include the compile flags for this target's objects.
include src/tests/CMakeFiles/sandArrangementTest.dir/flags.make

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o: src/tests/CMakeFiles/sandArrangementTest.dir/flags.make
src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o: src/tests/sandArrangementTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cezary/CLionProjects/pw3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o"
	cd /home/cezary/CLionProjects/pw3/src/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o -c /home/cezary/CLionProjects/pw3/src/tests/sandArrangementTest.cpp

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.i"
	cd /home/cezary/CLionProjects/pw3/src/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cezary/CLionProjects/pw3/src/tests/sandArrangementTest.cpp > CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.i

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.s"
	cd /home/cezary/CLionProjects/pw3/src/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cezary/CLionProjects/pw3/src/tests/sandArrangementTest.cpp -o CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.s

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.requires:

.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.requires

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.provides: src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.requires
	$(MAKE) -f src/tests/CMakeFiles/sandArrangementTest.dir/build.make src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.provides.build
.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.provides

src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.provides.build: src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o


# Object files for target sandArrangementTest
sandArrangementTest_OBJECTS = \
"CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o"

# External object files for target sandArrangementTest
sandArrangementTest_EXTERNAL_OBJECTS =

src/tests/sandArrangementTest: src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o
src/tests/sandArrangementTest: src/tests/CMakeFiles/sandArrangementTest.dir/build.make
src/tests/sandArrangementTest: src/tests/CMakeFiles/sandArrangementTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cezary/CLionProjects/pw3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sandArrangementTest"
	cd /home/cezary/CLionProjects/pw3/src/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sandArrangementTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tests/CMakeFiles/sandArrangementTest.dir/build: src/tests/sandArrangementTest

.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/build

src/tests/CMakeFiles/sandArrangementTest.dir/requires: src/tests/CMakeFiles/sandArrangementTest.dir/sandArrangementTest.cpp.o.requires

.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/requires

src/tests/CMakeFiles/sandArrangementTest.dir/clean:
	cd /home/cezary/CLionProjects/pw3/src/tests && $(CMAKE_COMMAND) -P CMakeFiles/sandArrangementTest.dir/cmake_clean.cmake
.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/clean

src/tests/CMakeFiles/sandArrangementTest.dir/depend:
	cd /home/cezary/CLionProjects/pw3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cezary/CLionProjects/pw3 /home/cezary/CLionProjects/pw3/src/tests /home/cezary/CLionProjects/pw3 /home/cezary/CLionProjects/pw3/src/tests /home/cezary/CLionProjects/pw3/src/tests/CMakeFiles/sandArrangementTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tests/CMakeFiles/sandArrangementTest.dir/depend

