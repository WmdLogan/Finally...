# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\CLionProjects\Leetcode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\CLionProjects\Leetcode\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bit.dir/flags.make

CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.obj: CMakeFiles/bit.dir/flags.make
CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.obj: ../DataStructure/Bit_2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.obj"
	D:\Mingw\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\bit.dir\DataStructure\Bit_2.cpp.obj -c D:\CLionProjects\Leetcode\DataStructure\Bit_2.cpp

CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.i"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLionProjects\Leetcode\DataStructure\Bit_2.cpp > CMakeFiles\bit.dir\DataStructure\Bit_2.cpp.i

CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.s"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLionProjects\Leetcode\DataStructure\Bit_2.cpp -o CMakeFiles\bit.dir\DataStructure\Bit_2.cpp.s

# Object files for target bit
bit_OBJECTS = \
"CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.obj"

# External object files for target bit
bit_EXTERNAL_OBJECTS =

bit.exe: CMakeFiles/bit.dir/DataStructure/Bit_2.cpp.obj
bit.exe: CMakeFiles/bit.dir/build.make
bit.exe: CMakeFiles/bit.dir/linklibs.rsp
bit.exe: CMakeFiles/bit.dir/objects1.rsp
bit.exe: CMakeFiles/bit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bit.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bit.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bit.dir/build: bit.exe

.PHONY : CMakeFiles/bit.dir/build

CMakeFiles/bit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bit.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bit.dir/clean

CMakeFiles/bit.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles\bit.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bit.dir/depend

