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
CMAKE_SOURCE_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid

# Include any dependencies generated for this target.
include CMakeFiles/threadpool_shared.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/threadpool_shared.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/threadpool_shared.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threadpool_shared.dir/flags.make

CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj: CMakeFiles/threadpool_shared.dir/flags.make
CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj: CMakeFiles/threadpool_shared.dir/includes_CXX.rsp
CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/src/threadpool_Last.cpp
CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj: CMakeFiles/threadpool_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj -MF CMakeFiles\threadpool_shared.dir\src\threadpool_Last.cpp.obj.d -o CMakeFiles\threadpool_shared.dir\src\threadpool_Last.cpp.obj -c D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\src\threadpool_Last.cpp

CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.i"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\src\threadpool_Last.cpp > CMakeFiles\threadpool_shared.dir\src\threadpool_Last.cpp.i

CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.s"
	D:\Xu\Softwares\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\src\threadpool_Last.cpp -o CMakeFiles\threadpool_shared.dir\src\threadpool_Last.cpp.s

# Object files for target threadpool_shared
threadpool_shared_OBJECTS = \
"CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj"

# External object files for target threadpool_shared
threadpool_shared_EXTERNAL_OBJECTS =

D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll: CMakeFiles/threadpool_shared.dir/src/threadpool_Last.cpp.obj
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll: CMakeFiles/threadpool_shared.dir/build.make
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll: CMakeFiles/threadpool_shared.dir/linkLibs.rsp
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll: CMakeFiles/threadpool_shared.dir/objects1.rsp
D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll: CMakeFiles/threadpool_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\lib\libthreadpool_shared.dll"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\threadpool_shared.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threadpool_shared.dir/build: D:/Xu/Desktop/Le/git/Project/Threadpool/Threadpool_Last/lib/libthreadpool_shared.dll
.PHONY : CMakeFiles/threadpool_shared.dir/build

CMakeFiles/threadpool_shared.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\threadpool_shared.dir\cmake_clean.cmake
.PHONY : CMakeFiles/threadpool_shared.dir/clean

CMakeFiles/threadpool_shared.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid D:\Xu\Desktop\Le\git\Project\Threadpool\Threadpool_Last\bulid\CMakeFiles\threadpool_shared.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/threadpool_shared.dir/depend

