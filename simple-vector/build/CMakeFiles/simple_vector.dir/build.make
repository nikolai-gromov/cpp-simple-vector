# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/nikolai/practicum/cpp-simple-vector/simple-vector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nikolai/practicum/cpp-simple-vector/simple-vector/build

# Include any dependencies generated for this target.
include CMakeFiles/simple_vector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simple_vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simple_vector.dir/flags.make

CMakeFiles/simple_vector.dir/main.cpp.o: CMakeFiles/simple_vector.dir/flags.make
CMakeFiles/simple_vector.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikolai/practicum/cpp-simple-vector/simple-vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simple_vector.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simple_vector.dir/main.cpp.o -c /home/nikolai/practicum/cpp-simple-vector/simple-vector/main.cpp

CMakeFiles/simple_vector.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_vector.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikolai/practicum/cpp-simple-vector/simple-vector/main.cpp > CMakeFiles/simple_vector.dir/main.cpp.i

CMakeFiles/simple_vector.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_vector.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikolai/practicum/cpp-simple-vector/simple-vector/main.cpp -o CMakeFiles/simple_vector.dir/main.cpp.s

# Object files for target simple_vector
simple_vector_OBJECTS = \
"CMakeFiles/simple_vector.dir/main.cpp.o"

# External object files for target simple_vector
simple_vector_EXTERNAL_OBJECTS =

simple_vector: CMakeFiles/simple_vector.dir/main.cpp.o
simple_vector: CMakeFiles/simple_vector.dir/build.make
simple_vector: CMakeFiles/simple_vector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nikolai/practicum/cpp-simple-vector/simple-vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable simple_vector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple_vector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simple_vector.dir/build: simple_vector

.PHONY : CMakeFiles/simple_vector.dir/build

CMakeFiles/simple_vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simple_vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simple_vector.dir/clean

CMakeFiles/simple_vector.dir/depend:
	cd /home/nikolai/practicum/cpp-simple-vector/simple-vector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikolai/practicum/cpp-simple-vector/simple-vector /home/nikolai/practicum/cpp-simple-vector/simple-vector /home/nikolai/practicum/cpp-simple-vector/simple-vector/build /home/nikolai/practicum/cpp-simple-vector/simple-vector/build /home/nikolai/practicum/cpp-simple-vector/simple-vector/build/CMakeFiles/simple_vector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple_vector.dir/depend
