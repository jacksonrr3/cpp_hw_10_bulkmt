# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/cmake-3.12.4/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.12.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt

# Include any dependencies generated for this target.
include CMakeFiles/bulkmt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bulkmt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bulkmt.dir/flags.make

CMakeFiles/bulkmt.dir/src/main.cpp.o: CMakeFiles/bulkmt.dir/flags.make
CMakeFiles/bulkmt.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bulkmt.dir/src/main.cpp.o"
	/usr/local/clang-7.0.0/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bulkmt.dir/src/main.cpp.o -c /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/src/main.cpp

CMakeFiles/bulkmt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bulkmt.dir/src/main.cpp.i"
	/usr/local/clang-7.0.0/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/src/main.cpp > CMakeFiles/bulkmt.dir/src/main.cpp.i

CMakeFiles/bulkmt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bulkmt.dir/src/main.cpp.s"
	/usr/local/clang-7.0.0/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/src/main.cpp -o CMakeFiles/bulkmt.dir/src/main.cpp.s

# Object files for target bulkmt
bulkmt_OBJECTS = \
"CMakeFiles/bulkmt.dir/src/main.cpp.o"

# External object files for target bulkmt
bulkmt_EXTERNAL_OBJECTS =

bulkmt: CMakeFiles/bulkmt.dir/src/main.cpp.o
bulkmt: CMakeFiles/bulkmt.dir/build.make
bulkmt: CMakeFiles/bulkmt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bulkmt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bulkmt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bulkmt.dir/build: bulkmt

.PHONY : CMakeFiles/bulkmt.dir/build

CMakeFiles/bulkmt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bulkmt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bulkmt.dir/clean

CMakeFiles/bulkmt.dir/depend:
	cd /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt /home/travis/build/jacksonrr3/cpp_hw_10_bulkmt/CMakeFiles/bulkmt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bulkmt.dir/depend

