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
include CMakeFiles/divide_conquer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/divide_conquer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/divide_conquer.dir/flags.make

CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.obj: CMakeFiles/divide_conquer.dir/flags.make
CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.obj: ../Algorithm/DevideConquer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.obj"
	D:\Mingw\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\divide_conquer.dir\Algorithm\DevideConquer.cpp.obj -c D:\CLionProjects\Leetcode\Algorithm\DevideConquer.cpp

CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.i"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLionProjects\Leetcode\Algorithm\DevideConquer.cpp > CMakeFiles\divide_conquer.dir\Algorithm\DevideConquer.cpp.i

CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.s"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLionProjects\Leetcode\Algorithm\DevideConquer.cpp -o CMakeFiles\divide_conquer.dir\Algorithm\DevideConquer.cpp.s

# Object files for target divide_conquer
divide_conquer_OBJECTS = \
"CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.obj"

# External object files for target divide_conquer
divide_conquer_EXTERNAL_OBJECTS =

divide_conquer.exe: CMakeFiles/divide_conquer.dir/Algorithm/DevideConquer.cpp.obj
divide_conquer.exe: CMakeFiles/divide_conquer.dir/build.make
divide_conquer.exe: CMakeFiles/divide_conquer.dir/linklibs.rsp
divide_conquer.exe: CMakeFiles/divide_conquer.dir/objects1.rsp
divide_conquer.exe: CMakeFiles/divide_conquer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable divide_conquer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\divide_conquer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/divide_conquer.dir/build: divide_conquer.exe

.PHONY : CMakeFiles/divide_conquer.dir/build

CMakeFiles/divide_conquer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\divide_conquer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/divide_conquer.dir/clean

CMakeFiles/divide_conquer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles\divide_conquer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/divide_conquer.dir/depend

