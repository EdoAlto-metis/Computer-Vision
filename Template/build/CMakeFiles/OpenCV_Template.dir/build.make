# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/Edoardo/Gith/Computer-Vision/Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/Edoardo/Gith/Computer-Vision/Template/build

# Include any dependencies generated for this target.
include CMakeFiles/OpenCV_Template.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenCV_Template.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenCV_Template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenCV_Template.dir/flags.make

CMakeFiles/OpenCV_Template.dir/main.cpp.obj: CMakeFiles/OpenCV_Template.dir/flags.make
CMakeFiles/OpenCV_Template.dir/main.cpp.obj: CMakeFiles/OpenCV_Template.dir/includes_CXX.rsp
CMakeFiles/OpenCV_Template.dir/main.cpp.obj: ../main.cpp
CMakeFiles/OpenCV_Template.dir/main.cpp.obj: CMakeFiles/OpenCV_Template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/Edoardo/Gith/Computer-Vision/Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenCV_Template.dir/main.cpp.obj"
	C:/cygwin64/bin/x86_64-pc-cygwin-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenCV_Template.dir/main.cpp.obj -MF CMakeFiles/OpenCV_Template.dir/main.cpp.obj.d -o CMakeFiles/OpenCV_Template.dir/main.cpp.obj -c C:/Users/Edoardo/Gith/Computer-Vision/Template/main.cpp

CMakeFiles/OpenCV_Template.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCV_Template.dir/main.cpp.i"
	C:/cygwin64/bin/x86_64-pc-cygwin-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Edoardo/Gith/Computer-Vision/Template/main.cpp > CMakeFiles/OpenCV_Template.dir/main.cpp.i

CMakeFiles/OpenCV_Template.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCV_Template.dir/main.cpp.s"
	C:/cygwin64/bin/x86_64-pc-cygwin-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Edoardo/Gith/Computer-Vision/Template/main.cpp -o CMakeFiles/OpenCV_Template.dir/main.cpp.s

# Object files for target OpenCV_Template
OpenCV_Template_OBJECTS = \
"CMakeFiles/OpenCV_Template.dir/main.cpp.obj"

# External object files for target OpenCV_Template
OpenCV_Template_EXTERNAL_OBJECTS =

OpenCV_Template.exe: CMakeFiles/OpenCV_Template.dir/main.cpp.obj
OpenCV_Template.exe: CMakeFiles/OpenCV_Template.dir/build.make
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: C:/OpenCV-4.5.5/opencv/build/x64/vc15/lib/opencv_world455d.lib
OpenCV_Template.exe: CMakeFiles/OpenCV_Template.dir/linklibs.rsp
OpenCV_Template.exe: CMakeFiles/OpenCV_Template.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/Users/Edoardo/Gith/Computer-Vision/Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenCV_Template.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/OpenCV_Template.dir/objects.a
	C:/cygwin64/bin/ar.exe qc CMakeFiles/OpenCV_Template.dir/objects.a @CMakeFiles/OpenCV_Template.dir/objects1.rsp
	C:/cygwin64/bin/x86_64-pc-cygwin-g++.exe -g -Wl,--whole-archive CMakeFiles/OpenCV_Template.dir/objects.a -Wl,--no-whole-archive -o OpenCV_Template.exe -Wl,--out-implib,libOpenCV_Template.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/OpenCV_Template.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/OpenCV_Template.dir/build: OpenCV_Template.exe
.PHONY : CMakeFiles/OpenCV_Template.dir/build

CMakeFiles/OpenCV_Template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenCV_Template.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenCV_Template.dir/clean

CMakeFiles/OpenCV_Template.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Edoardo/Gith/Computer-Vision/Template C:/Users/Edoardo/Gith/Computer-Vision/Template C:/Users/Edoardo/Gith/Computer-Vision/Template/build C:/Users/Edoardo/Gith/Computer-Vision/Template/build C:/Users/Edoardo/Gith/Computer-Vision/Template/build/CMakeFiles/OpenCV_Template.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenCV_Template.dir/depend

