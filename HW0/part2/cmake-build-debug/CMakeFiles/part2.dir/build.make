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
CMAKE_SOURCE_DIR = C:\Users\Ido\CLionProjects\part2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ido\CLionProjects\part2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/part2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/part2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/part2.dir/flags.make

CMakeFiles/part2.dir/mtm_buggy.c.obj: CMakeFiles/part2.dir/flags.make
CMakeFiles/part2.dir/mtm_buggy.c.obj: ../mtm_buggy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ido\CLionProjects\part2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/part2.dir/mtm_buggy.c.obj"
	C:\TDM-GCC-32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\part2.dir\mtm_buggy.c.obj   -c C:\Users\Ido\CLionProjects\part2\mtm_buggy.c

CMakeFiles/part2.dir/mtm_buggy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/part2.dir/mtm_buggy.c.i"
	C:\TDM-GCC-32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Ido\CLionProjects\part2\mtm_buggy.c > CMakeFiles\part2.dir\mtm_buggy.c.i

CMakeFiles/part2.dir/mtm_buggy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/part2.dir/mtm_buggy.c.s"
	C:\TDM-GCC-32\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Ido\CLionProjects\part2\mtm_buggy.c -o CMakeFiles\part2.dir\mtm_buggy.c.s

CMakeFiles/part2.dir/mtm_buggy.c.obj.requires:

.PHONY : CMakeFiles/part2.dir/mtm_buggy.c.obj.requires

CMakeFiles/part2.dir/mtm_buggy.c.obj.provides: CMakeFiles/part2.dir/mtm_buggy.c.obj.requires
	$(MAKE) -f CMakeFiles\part2.dir\build.make CMakeFiles/part2.dir/mtm_buggy.c.obj.provides.build
.PHONY : CMakeFiles/part2.dir/mtm_buggy.c.obj.provides

CMakeFiles/part2.dir/mtm_buggy.c.obj.provides.build: CMakeFiles/part2.dir/mtm_buggy.c.obj


# Object files for target part2
part2_OBJECTS = \
"CMakeFiles/part2.dir/mtm_buggy.c.obj"

# External object files for target part2
part2_EXTERNAL_OBJECTS =

part2.exe: CMakeFiles/part2.dir/mtm_buggy.c.obj
part2.exe: CMakeFiles/part2.dir/build.make
part2.exe: CMakeFiles/part2.dir/linklibs.rsp
part2.exe: CMakeFiles/part2.dir/objects1.rsp
part2.exe: CMakeFiles/part2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ido\CLionProjects\part2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable part2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\part2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/part2.dir/build: part2.exe

.PHONY : CMakeFiles/part2.dir/build

CMakeFiles/part2.dir/requires: CMakeFiles/part2.dir/mtm_buggy.c.obj.requires

.PHONY : CMakeFiles/part2.dir/requires

CMakeFiles/part2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\part2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/part2.dir/clean

CMakeFiles/part2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Ido\CLionProjects\part2 C:\Users\Ido\CLionProjects\part2 C:\Users\Ido\CLionProjects\part2\cmake-build-debug C:\Users\Ido\CLionProjects\part2\cmake-build-debug C:\Users\Ido\CLionProjects\part2\cmake-build-debug\CMakeFiles\part2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/part2.dir/depend

