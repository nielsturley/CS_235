# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/nielsturley/CLionProjects/Lab 01 Grades"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lab_01_Grades.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab_01_Grades.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab_01_Grades.dir/flags.make

CMakeFiles/Lab_01_Grades.dir/main.cpp.o: CMakeFiles/Lab_01_Grades.dir/flags.make
CMakeFiles/Lab_01_Grades.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab_01_Grades.dir/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Lab_01_Grades.dir/main.cpp.o -c "/Users/nielsturley/CLionProjects/Lab 01 Grades/main.cpp"

CMakeFiles/Lab_01_Grades.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_01_Grades.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/nielsturley/CLionProjects/Lab 01 Grades/main.cpp" > CMakeFiles/Lab_01_Grades.dir/main.cpp.i

CMakeFiles/Lab_01_Grades.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_01_Grades.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/nielsturley/CLionProjects/Lab 01 Grades/main.cpp" -o CMakeFiles/Lab_01_Grades.dir/main.cpp.s

# Object files for target Lab_01_Grades
Lab_01_Grades_OBJECTS = \
"CMakeFiles/Lab_01_Grades.dir/main.cpp.o"

# External object files for target Lab_01_Grades
Lab_01_Grades_EXTERNAL_OBJECTS =

Lab_01_Grades: CMakeFiles/Lab_01_Grades.dir/main.cpp.o
Lab_01_Grades: CMakeFiles/Lab_01_Grades.dir/build.make
Lab_01_Grades: CMakeFiles/Lab_01_Grades.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Lab_01_Grades"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab_01_Grades.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab_01_Grades.dir/build: Lab_01_Grades

.PHONY : CMakeFiles/Lab_01_Grades.dir/build

CMakeFiles/Lab_01_Grades.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab_01_Grades.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab_01_Grades.dir/clean

CMakeFiles/Lab_01_Grades.dir/depend:
	cd "/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/nielsturley/CLionProjects/Lab 01 Grades" "/Users/nielsturley/CLionProjects/Lab 01 Grades" "/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug" "/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug" "/Users/nielsturley/CLionProjects/Lab 01 Grades/cmake-build-debug/CMakeFiles/Lab_01_Grades.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab_01_Grades.dir/depend

