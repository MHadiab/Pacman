# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\ASUS\Desktop\bp project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\ASUS\Desktop\bp project\cmake-build-debug"

# Utility rule file for update_mappings.

# Include any custom commands dependencies for this target.
include vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/progress.make

vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="C:\Users\ASUS\Desktop\bp project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd /d C:\Users\ASUS\Desktop\BPPROJ~1\vendor\raylib\src\external\glfw\src && "C:\Program Files\JetBrains\CLion 2024.3\bin\cmake\win\x64\bin\cmake.exe" -P "C:/Users/ASUS/Desktop/bp project/vendor/raylib/src/external/glfw/CMake/GenerateMappings.cmake" mappings.h.in mappings.h

update_mappings: vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings
update_mappings: vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build.make
.PHONY : update_mappings

# Rule to build all files generated by this target.
vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings
.PHONY : vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/build

vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd /d C:\Users\ASUS\Desktop\BPPROJ~1\CMAKE-~1\vendor\raylib\raylib\external\glfw\src && $(CMAKE_COMMAND) -P CMakeFiles\update_mappings.dir\cmake_clean.cmake
.PHONY : vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/clean

vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\ASUS\Desktop\bp project" "C:\Users\ASUS\Desktop\bp project\vendor\raylib\src\external\glfw\src" "C:\Users\ASUS\Desktop\bp project\cmake-build-debug" "C:\Users\ASUS\Desktop\bp project\cmake-build-debug\vendor\raylib\raylib\external\glfw\src" "C:\Users\ASUS\Desktop\bp project\cmake-build-debug\vendor\raylib\raylib\external\glfw\src\CMakeFiles\update_mappings.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : vendor/raylib/raylib/external/glfw/src/CMakeFiles/update_mappings.dir/depend

