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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gary/Documents/Coding/C++/Poole

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gary/Documents/Coding/C++/Poole/build

# Include any dependencies generated for this target.
include CMakeFiles/Poole_Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Poole_Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Poole_Test.dir/flags.make

CMakeFiles/Poole_Test.dir/src/main.cpp.o: CMakeFiles/Poole_Test.dir/flags.make
CMakeFiles/Poole_Test.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gary/Documents/Coding/C++/Poole/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Poole_Test.dir/src/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Poole_Test.dir/src/main.cpp.o -c /home/gary/Documents/Coding/C++/Poole/src/main.cpp

CMakeFiles/Poole_Test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Poole_Test.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gary/Documents/Coding/C++/Poole/src/main.cpp > CMakeFiles/Poole_Test.dir/src/main.cpp.i

CMakeFiles/Poole_Test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Poole_Test.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gary/Documents/Coding/C++/Poole/src/main.cpp -o CMakeFiles/Poole_Test.dir/src/main.cpp.s

CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o: CMakeFiles/Poole_Test.dir/flags.make
CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o: ../include/Poole/Poole.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gary/Documents/Coding/C++/Poole/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o -c /home/gary/Documents/Coding/C++/Poole/include/Poole/Poole.cpp

CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gary/Documents/Coding/C++/Poole/include/Poole/Poole.cpp > CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.i

CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gary/Documents/Coding/C++/Poole/include/Poole/Poole.cpp -o CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.s

# Object files for target Poole_Test
Poole_Test_OBJECTS = \
"CMakeFiles/Poole_Test.dir/src/main.cpp.o" \
"CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o"

# External object files for target Poole_Test
Poole_Test_EXTERNAL_OBJECTS =

Poole_Test: CMakeFiles/Poole_Test.dir/src/main.cpp.o
Poole_Test: CMakeFiles/Poole_Test.dir/include/Poole/Poole.cpp.o
Poole_Test: CMakeFiles/Poole_Test.dir/build.make
Poole_Test: CMakeFiles/Poole_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gary/Documents/Coding/C++/Poole/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Poole_Test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Poole_Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Poole_Test.dir/build: Poole_Test

.PHONY : CMakeFiles/Poole_Test.dir/build

CMakeFiles/Poole_Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Poole_Test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Poole_Test.dir/clean

CMakeFiles/Poole_Test.dir/depend:
	cd /home/gary/Documents/Coding/C++/Poole/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gary/Documents/Coding/C++/Poole /home/gary/Documents/Coding/C++/Poole /home/gary/Documents/Coding/C++/Poole/build /home/gary/Documents/Coding/C++/Poole/build /home/gary/Documents/Coding/C++/Poole/build/CMakeFiles/Poole_Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Poole_Test.dir/depend

