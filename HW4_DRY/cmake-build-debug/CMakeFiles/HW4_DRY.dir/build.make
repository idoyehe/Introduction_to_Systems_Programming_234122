# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\JetBrains\CLion 2016.3.4\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\JetBrains\CLion 2016.3.4\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ido\CLionProjects\HW4_DRY

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW4_DRY.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW4_DRY.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW4_DRY.dir/flags.make

CMakeFiles/HW4_DRY.dir/main.cpp.obj: CMakeFiles/HW4_DRY.dir/flags.make
CMakeFiles/HW4_DRY.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW4_DRY.dir/main.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_DRY.dir\main.cpp.obj -c C:\Users\Ido\CLionProjects\HW4_DRY\main.cpp

CMakeFiles/HW4_DRY.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_DRY.dir/main.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ido\CLionProjects\HW4_DRY\main.cpp > CMakeFiles\HW4_DRY.dir\main.cpp.i

CMakeFiles/HW4_DRY.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_DRY.dir/main.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Ido\CLionProjects\HW4_DRY\main.cpp -o CMakeFiles\HW4_DRY.dir\main.cpp.s

CMakeFiles/HW4_DRY.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_DRY.dir/main.cpp.obj.requires

CMakeFiles/HW4_DRY.dir/main.cpp.obj.provides: CMakeFiles/HW4_DRY.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_DRY.dir\build.make CMakeFiles/HW4_DRY.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_DRY.dir/main.cpp.obj.provides

CMakeFiles/HW4_DRY.dir/main.cpp.obj.provides.build: CMakeFiles/HW4_DRY.dir/main.cpp.obj


# Object files for target HW4_DRY
HW4_DRY_OBJECTS = \
"CMakeFiles/HW4_DRY.dir/main.cpp.obj"

# External object files for target HW4_DRY
HW4_DRY_EXTERNAL_OBJECTS =

HW4_DRY.exe: CMakeFiles/HW4_DRY.dir/main.cpp.obj
HW4_DRY.exe: CMakeFiles/HW4_DRY.dir/build.make
HW4_DRY.exe: CMakeFiles/HW4_DRY.dir/linklibs.rsp
HW4_DRY.exe: CMakeFiles/HW4_DRY.dir/objects1.rsp
HW4_DRY.exe: CMakeFiles/HW4_DRY.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW4_DRY.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW4_DRY.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW4_DRY.dir/build: HW4_DRY.exe

.PHONY : CMakeFiles/HW4_DRY.dir/build

CMakeFiles/HW4_DRY.dir/requires: CMakeFiles/HW4_DRY.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/HW4_DRY.dir/requires

CMakeFiles/HW4_DRY.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW4_DRY.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW4_DRY.dir/clean

CMakeFiles/HW4_DRY.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ido\CLionProjects\HW4_DRY C:\Users\Ido\CLionProjects\HW4_DRY C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug C:\Users\Ido\CLionProjects\HW4_DRY\cmake-build-debug\CMakeFiles\HW4_DRY.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW4_DRY.dir/depend
