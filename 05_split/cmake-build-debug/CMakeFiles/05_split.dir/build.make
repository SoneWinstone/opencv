# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = H:\Code\OpenCV\05_split

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = H:\Code\OpenCV\05_split\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/05_split.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/05_split.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/05_split.dir/flags.make

CMakeFiles/05_split.dir/main.cpp.obj: CMakeFiles/05_split.dir/flags.make
CMakeFiles/05_split.dir/main.cpp.obj: CMakeFiles/05_split.dir/includes_CXX.rsp
CMakeFiles/05_split.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=H:\Code\OpenCV\05_split\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/05_split.dir/main.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\05_split.dir\main.cpp.obj -c H:\Code\OpenCV\05_split\main.cpp

CMakeFiles/05_split.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/05_split.dir/main.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E H:\Code\OpenCV\05_split\main.cpp > CMakeFiles\05_split.dir\main.cpp.i

CMakeFiles/05_split.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/05_split.dir/main.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S H:\Code\OpenCV\05_split\main.cpp -o CMakeFiles\05_split.dir\main.cpp.s

CMakeFiles/05_split.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/05_split.dir/main.cpp.obj.requires

CMakeFiles/05_split.dir/main.cpp.obj.provides: CMakeFiles/05_split.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\05_split.dir\build.make CMakeFiles/05_split.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/05_split.dir/main.cpp.obj.provides

CMakeFiles/05_split.dir/main.cpp.obj.provides.build: CMakeFiles/05_split.dir/main.cpp.obj


# Object files for target 05_split
05_split_OBJECTS = \
"CMakeFiles/05_split.dir/main.cpp.obj"

# External object files for target 05_split
05_split_EXTERNAL_OBJECTS =

05_split.exe: CMakeFiles/05_split.dir/main.cpp.obj
05_split.exe: CMakeFiles/05_split.dir/build.make
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_shape320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_stitching320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_superres320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_videostab320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_objdetect320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_calib3d320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_features2d320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_flann320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_highgui320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_ml320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_photo320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_video320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_videoio320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_imgcodecs320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_imgproc320.dll.a
05_split.exe: E:/OpenCV3.2/opencv/MinGW-build/lib/libopencv_core320.dll.a
05_split.exe: CMakeFiles/05_split.dir/linklibs.rsp
05_split.exe: CMakeFiles/05_split.dir/objects1.rsp
05_split.exe: CMakeFiles/05_split.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=H:\Code\OpenCV\05_split\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 05_split.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\05_split.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/05_split.dir/build: 05_split.exe

.PHONY : CMakeFiles/05_split.dir/build

CMakeFiles/05_split.dir/requires: CMakeFiles/05_split.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/05_split.dir/requires

CMakeFiles/05_split.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\05_split.dir\cmake_clean.cmake
.PHONY : CMakeFiles/05_split.dir/clean

CMakeFiles/05_split.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" H:\Code\OpenCV\05_split H:\Code\OpenCV\05_split H:\Code\OpenCV\05_split\cmake-build-debug H:\Code\OpenCV\05_split\cmake-build-debug H:\Code\OpenCV\05_split\cmake-build-debug\CMakeFiles\05_split.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/05_split.dir/depend
