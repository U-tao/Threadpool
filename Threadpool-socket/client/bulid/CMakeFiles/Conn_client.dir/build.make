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
CMAKE_COMMAND = D:\Xu\Softwares\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\Xu\Softwares\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid

# Include any dependencies generated for this target.
include CMakeFiles/Conn_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Conn_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Conn_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Conn_client.dir/flags.make

CMakeFiles/Conn_client.dir/client.cpp.obj: CMakeFiles/Conn_client.dir/flags.make
CMakeFiles/Conn_client.dir/client.cpp.obj: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool-socket/client/client.cpp
CMakeFiles/Conn_client.dir/client.cpp.obj: CMakeFiles/Conn_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Conn_client.dir/client.cpp.obj"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Conn_client.dir/client.cpp.obj -MF CMakeFiles\Conn_client.dir\client.cpp.obj.d -o CMakeFiles\Conn_client.dir\client.cpp.obj -c D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\client.cpp

CMakeFiles/Conn_client.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Conn_client.dir/client.cpp.i"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\client.cpp > CMakeFiles\Conn_client.dir\client.cpp.i

CMakeFiles/Conn_client.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Conn_client.dir/client.cpp.s"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\client.cpp -o CMakeFiles\Conn_client.dir\client.cpp.s

# Object files for target Conn_client
Conn_client_OBJECTS = \
"CMakeFiles/Conn_client.dir/client.cpp.obj"

# External object files for target Conn_client
Conn_client_EXTERNAL_OBJECTS =

Conn_client.exe: CMakeFiles/Conn_client.dir/client.cpp.obj
Conn_client.exe: CMakeFiles/Conn_client.dir/build.make
Conn_client.exe: CMakeFiles/Conn_client.dir/linkLibs.rsp
Conn_client.exe: CMakeFiles/Conn_client.dir/objects1.rsp
Conn_client.exe: CMakeFiles/Conn_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Conn_client.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Conn_client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Conn_client.dir/build: Conn_client.exe
.PHONY : CMakeFiles/Conn_client.dir/build

CMakeFiles/Conn_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Conn_client.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Conn_client.dir/clean

CMakeFiles/Conn_client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool-socket\client\bulid\CMakeFiles\Conn_client.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Conn_client.dir/depend

