# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW4_WET.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW4_WET.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW4_WET.dir/flags.make

CMakeFiles/HW4_WET.dir/Company.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/Company.cpp.obj: ../Company.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW4_WET.dir/Company.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\Company.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Company.cpp

CMakeFiles/HW4_WET.dir/Company.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/Company.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Company.cpp > CMakeFiles\HW4_WET.dir\Company.cpp.i

CMakeFiles/HW4_WET.dir/Company.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/Company.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Company.cpp -o CMakeFiles\HW4_WET.dir\Company.cpp.s

CMakeFiles/HW4_WET.dir/Company.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/Company.cpp.obj.requires

CMakeFiles/HW4_WET.dir/Company.cpp.obj.provides: CMakeFiles/HW4_WET.dir/Company.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/Company.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/Company.cpp.obj.provides

CMakeFiles/HW4_WET.dir/Company.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/Company.cpp.obj


CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj: ../tests/Company_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\tests\Company_test.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\tests\Company_test.cpp

CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\tests\Company_test.cpp > CMakeFiles\HW4_WET.dir\tests\Company_test.cpp.i

CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\tests\Company_test.cpp -o CMakeFiles\HW4_WET.dir\tests\Company_test.cpp.s

CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.requires

CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.provides: CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.provides

CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj


CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj: ../EscapeRoom.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\HW4_WET.dir\EscapeRoom.c.obj   -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoom.c

CMakeFiles/HW4_WET.dir/EscapeRoom.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW4_WET.dir/EscapeRoom.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoom.c > CMakeFiles\HW4_WET.dir\EscapeRoom.c.i

CMakeFiles/HW4_WET.dir/EscapeRoom.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW4_WET.dir/EscapeRoom.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoom.c -o CMakeFiles\HW4_WET.dir\EscapeRoom.c.s

CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.requires

CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.provides: CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.provides

CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.provides.build: CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj


CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj: ../EscapeRoomWrapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\EscapeRoomWrapper.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoomWrapper.cpp

CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoomWrapper.cpp > CMakeFiles\HW4_WET.dir\EscapeRoomWrapper.cpp.i

CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\EscapeRoomWrapper.cpp -o CMakeFiles\HW4_WET.dir\EscapeRoomWrapper.cpp.s

CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.requires

CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.provides: CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.provides

CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj


CMakeFiles/HW4_WET.dir/Enigma.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/Enigma.cpp.obj: ../Enigma.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/HW4_WET.dir/Enigma.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\Enigma.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Enigma.cpp

CMakeFiles/HW4_WET.dir/Enigma.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/Enigma.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Enigma.cpp > CMakeFiles\HW4_WET.dir\Enigma.cpp.i

CMakeFiles/HW4_WET.dir/Enigma.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/Enigma.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\Enigma.cpp -o CMakeFiles\HW4_WET.dir\Enigma.cpp.s

CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.requires

CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.provides: CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.provides

CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/Enigma.cpp.obj


CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj: ../ScaryRoom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\ScaryRoom.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\ScaryRoom.cpp

CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\ScaryRoom.cpp > CMakeFiles\HW4_WET.dir\ScaryRoom.cpp.i

CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\ScaryRoom.cpp -o CMakeFiles\HW4_WET.dir\ScaryRoom.cpp.s

CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.requires

CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.provides: CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.provides

CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj


CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj: CMakeFiles/HW4_WET.dir/flags.make
CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj: ../KidsRoom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW4_WET.dir\KidsRoom.cpp.obj -c C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\KidsRoom.cpp

CMakeFiles/HW4_WET.dir/KidsRoom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW4_WET.dir/KidsRoom.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\KidsRoom.cpp > CMakeFiles\HW4_WET.dir\KidsRoom.cpp.i

CMakeFiles/HW4_WET.dir/KidsRoom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW4_WET.dir/KidsRoom.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\KidsRoom.cpp -o CMakeFiles\HW4_WET.dir\KidsRoom.cpp.s

CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.requires:

.PHONY : CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.requires

CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.provides: CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.requires
	$(MAKE) -f CMakeFiles\HW4_WET.dir\build.make CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.provides.build
.PHONY : CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.provides

CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.provides.build: CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj


# Object files for target HW4_WET
HW4_WET_OBJECTS = \
"CMakeFiles/HW4_WET.dir/Company.cpp.obj" \
"CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj" \
"CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj" \
"CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj" \
"CMakeFiles/HW4_WET.dir/Enigma.cpp.obj" \
"CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj" \
"CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj"

# External object files for target HW4_WET
HW4_WET_EXTERNAL_OBJECTS =

HW4_WET.exe: CMakeFiles/HW4_WET.dir/Company.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/Enigma.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj
HW4_WET.exe: CMakeFiles/HW4_WET.dir/build.make
HW4_WET.exe: CMakeFiles/HW4_WET.dir/linklibs.rsp
HW4_WET.exe: CMakeFiles/HW4_WET.dir/objects1.rsp
HW4_WET.exe: CMakeFiles/HW4_WET.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable HW4_WET.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW4_WET.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW4_WET.dir/build: HW4_WET.exe

.PHONY : CMakeFiles/HW4_WET.dir/build

CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/Company.cpp.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/tests/Company_test.cpp.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/EscapeRoom.c.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/EscapeRoomWrapper.cpp.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/Enigma.cpp.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/ScaryRoom.cpp.obj.requires
CMakeFiles/HW4_WET.dir/requires: CMakeFiles/HW4_WET.dir/KidsRoom.cpp.obj.requires

.PHONY : CMakeFiles/HW4_WET.dir/requires

CMakeFiles/HW4_WET.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW4_WET.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW4_WET.dir/clean

CMakeFiles/HW4_WET.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug C:\Users\IdoYehe\CLionProjects\MATAM\HW4_WET\cmake-build-debug\CMakeFiles\HW4_WET.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW4_WET.dir/depend

