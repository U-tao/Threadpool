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
CMAKE_SOURCE_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid

# Include any dependencies generated for this target.
include CMakeFiles/threadpool_origin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/threadpool_origin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/threadpool_origin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threadpool_origin.dir/flags.make

CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj: CMakeFiles/threadpool_origin.dir/flags.make
CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj: CMakeFiles/threadpool_origin.dir/includes_CXX.rsp
CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/src/threadpool.cpp
CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj: CMakeFiles/threadpool_origin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj -MF CMakeFiles\threadpool_origin.dir\src\threadpool.cpp.obj.d -o CMakeFiles\threadpool_origin.dir\src\threadpool.cpp.obj -c D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\src\threadpool.cpp

CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.i"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\src\threadpool.cpp > CMakeFiles\threadpool_origin.dir\src\threadpool.cpp.i

CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.s"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\src\threadpool.cpp -o CMakeFiles\threadpool_origin.dir\src\threadpool.cpp.s

CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj: CMakeFiles/threadpool_origin.dir/flags.make
CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj: CMakeFiles/threadpool_origin.dir/includes_CXX.rsp
CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpooltest.cpp
CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj: CMakeFiles/threadpool_origin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj -MF CMakeFiles\threadpool_origin.dir\threadpooltest.cpp.obj.d -o CMakeFiles\threadpool_origin.dir\threadpooltest.cpp.obj -c D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\threadpooltest.cpp

CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.i"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\threadpooltest.cpp > CMakeFiles\threadpool_origin.dir\threadpooltest.cpp.i

CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.s"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\threadpooltest.cpp -o CMakeFiles\threadpool_origin.dir\threadpooltest.cpp.s

# Object files for target threadpool_origin
threadpool_origin_OBJECTS = \
"CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj" \
"CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj"

# External object files for target threadpool_origin
threadpool_origin_EXTERNAL_OBJECTS =

D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/src/threadpool.cpp.obj
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/threadpooltest.cpp.obj
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/build.make
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/linkLibs.rsp
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/objects1.rsp
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe: CMakeFiles/threadpool_origin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\threadpool_origin.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\threadpool_origin.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threadpool_origin.dir/build: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool/threadpool_origin.exe
.PHONY : CMakeFiles/threadpool_origin.dir/build

CMakeFiles/threadpool_origin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\threadpool_origin.dir\cmake_clean.cmake
.PHONY : CMakeFiles/threadpool_origin.dir/clean

CMakeFiles/threadpool_origin.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool\bulid\CMakeFiles\threadpool_origin.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/threadpool_origin.dir/depend

