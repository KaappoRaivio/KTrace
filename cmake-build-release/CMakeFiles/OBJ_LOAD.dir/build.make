# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/kaappo/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5080.54/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kaappo/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5080.54/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kaappo/git/cliontest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaappo/git/cliontest/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/OBJ_LOAD.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/OBJ_LOAD.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OBJ_LOAD.dir/flags.make

CMakeFiles/OBJ_LOAD.dir/load.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/load.cpp.o: ../load.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OBJ_LOAD.dir/load.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/load.cpp.o -c /home/kaappo/git/cliontest/load.cpp

CMakeFiles/OBJ_LOAD.dir/load.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/load.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/load.cpp > CMakeFiles/OBJ_LOAD.dir/load.cpp.i

CMakeFiles/OBJ_LOAD.dir/load.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/load.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/load.cpp -o CMakeFiles/OBJ_LOAD.dir/load.cpp.s

CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o: ../MyVector3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o -c /home/kaappo/git/cliontest/MyVector3.cpp

CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/MyVector3.cpp > CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.i

CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/MyVector3.cpp -o CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.s

CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o: ../SolidTexture.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o -c /home/kaappo/git/cliontest/SolidTexture.cpp

CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/SolidTexture.cpp > CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.i

CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/SolidTexture.cpp -o CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.s

CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o: ../Triangle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o -c /home/kaappo/git/cliontest/Triangle.cpp

CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Triangle.cpp > CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.i

CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Triangle.cpp -o CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.s

CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o: ../Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o -c /home/kaappo/git/cliontest/Camera.cpp

CMakeFiles/OBJ_LOAD.dir/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Camera.cpp > CMakeFiles/OBJ_LOAD.dir/Camera.cpp.i

CMakeFiles/OBJ_LOAD.dir/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Camera.cpp -o CMakeFiles/OBJ_LOAD.dir/Camera.cpp.s

CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o: ../SceneObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o -c /home/kaappo/git/cliontest/SceneObject.cpp

CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/SceneObject.cpp > CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.i

CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/SceneObject.cpp -o CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.s

CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o: ../Plane.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o -c /home/kaappo/git/cliontest/Plane.cpp

CMakeFiles/OBJ_LOAD.dir/Plane.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Plane.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Plane.cpp > CMakeFiles/OBJ_LOAD.dir/Plane.cpp.i

CMakeFiles/OBJ_LOAD.dir/Plane.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Plane.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Plane.cpp -o CMakeFiles/OBJ_LOAD.dir/Plane.cpp.s

CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o: ../Ray.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o -c /home/kaappo/git/cliontest/Ray.cpp

CMakeFiles/OBJ_LOAD.dir/Ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Ray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Ray.cpp > CMakeFiles/OBJ_LOAD.dir/Ray.cpp.i

CMakeFiles/OBJ_LOAD.dir/Ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Ray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Ray.cpp -o CMakeFiles/OBJ_LOAD.dir/Ray.cpp.s

CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o: ../Intensity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o -c /home/kaappo/git/cliontest/Intensity.cpp

CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Intensity.cpp > CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.i

CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Intensity.cpp -o CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.s

CMakeFiles/OBJ_LOAD.dir/Color.cpp.o: CMakeFiles/OBJ_LOAD.dir/flags.make
CMakeFiles/OBJ_LOAD.dir/Color.cpp.o: ../Color.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/OBJ_LOAD.dir/Color.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OBJ_LOAD.dir/Color.cpp.o -c /home/kaappo/git/cliontest/Color.cpp

CMakeFiles/OBJ_LOAD.dir/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OBJ_LOAD.dir/Color.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaappo/git/cliontest/Color.cpp > CMakeFiles/OBJ_LOAD.dir/Color.cpp.i

CMakeFiles/OBJ_LOAD.dir/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OBJ_LOAD.dir/Color.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaappo/git/cliontest/Color.cpp -o CMakeFiles/OBJ_LOAD.dir/Color.cpp.s

# Object files for target OBJ_LOAD
OBJ_LOAD_OBJECTS = \
"CMakeFiles/OBJ_LOAD.dir/load.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o" \
"CMakeFiles/OBJ_LOAD.dir/Color.cpp.o"

# External object files for target OBJ_LOAD
OBJ_LOAD_EXTERNAL_OBJECTS =

OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/load.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/MyVector3.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/SolidTexture.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Triangle.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Camera.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/SceneObject.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Plane.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Ray.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Intensity.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/Color.cpp.o
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/build.make
OBJ_LOAD: CMakeFiles/OBJ_LOAD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kaappo/git/cliontest/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable OBJ_LOAD"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OBJ_LOAD.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OBJ_LOAD.dir/build: OBJ_LOAD
.PHONY : CMakeFiles/OBJ_LOAD.dir/build

CMakeFiles/OBJ_LOAD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OBJ_LOAD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OBJ_LOAD.dir/clean

CMakeFiles/OBJ_LOAD.dir/depend:
	cd /home/kaappo/git/cliontest/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kaappo/git/cliontest /home/kaappo/git/cliontest /home/kaappo/git/cliontest/cmake-build-release /home/kaappo/git/cliontest/cmake-build-release /home/kaappo/git/cliontest/cmake-build-release/CMakeFiles/OBJ_LOAD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OBJ_LOAD.dir/depend

