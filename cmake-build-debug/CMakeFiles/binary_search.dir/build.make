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
include CMakeFiles/binary_search.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/binary_search.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/binary_search.dir/flags.make

CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.obj: CMakeFiles/binary_search.dir/flags.make
CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.obj: ../Algorithm/BinarySearch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.obj"
	D:\Mingw\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\binary_search.dir\Algorithm\BinarySearch.cpp.obj -c D:\CLionProjects\Leetcode\Algorithm\BinarySearch.cpp

CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.i"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\CLionProjects\Leetcode\Algorithm\BinarySearch.cpp > CMakeFiles\binary_search.dir\Algorithm\BinarySearch.cpp.i

CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.s"
	D:\Mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\CLionProjects\Leetcode\Algorithm\BinarySearch.cpp -o CMakeFiles\binary_search.dir\Algorithm\BinarySearch.cpp.s

# Object files for target binary_search
binary_search_OBJECTS = \
"CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.obj"

# External object files for target binary_search
binary_search_EXTERNAL_OBJECTS =

binary_search.exe: CMakeFiles/binary_search.dir/Algorithm/BinarySearch.cpp.obj
binary_search.exe: CMakeFiles/binary_search.dir/build.make
binary_search.exe: CMakeFiles/binary_search.dir/linklibs.rsp
binary_search.exe: CMakeFiles/binary_search.dir/objects1.rsp
binary_search.exe: CMakeFiles/binary_search.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable binary_search.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\binary_search.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/binary_search.dir/build: binary_search.exe

.PHONY : CMakeFiles/binary_search.dir/build

CMakeFiles/binary_search.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\binary_search.dir\cmake_clean.cmake
.PHONY : CMakeFiles/binary_search.dir/clean

CMakeFiles/binary_search.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug D:\CLionProjects\Leetcode\cmake-build-debug\CMakeFiles\binary_search.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/binary_search.dir/depend

