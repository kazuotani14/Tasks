# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/icubuser/mc/install/Tasks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/icubuser/mc/install/Tasks/build

# Include any dependencies generated for this target.
include binding/python/CMakeFiles/_tasks.dir/depend.make

# Include the progress variables for this target.
include binding/python/CMakeFiles/_tasks.dir/progress.make

# Include the compile flags for this target's objects.
include binding/python/CMakeFiles/_tasks.dir/flags.make

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o: binding/python/CMakeFiles/_tasks.dir/flags.make
binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o: binding/python/tasks.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/icubuser/mc/install/Tasks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o"
	cd /home/icubuser/mc/install/Tasks/build/binding/python && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/_tasks.dir/tasks.cpp.o -c /home/icubuser/mc/install/Tasks/build/binding/python/tasks.cpp

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_tasks.dir/tasks.cpp.i"
	cd /home/icubuser/mc/install/Tasks/build/binding/python && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/icubuser/mc/install/Tasks/build/binding/python/tasks.cpp > CMakeFiles/_tasks.dir/tasks.cpp.i

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_tasks.dir/tasks.cpp.s"
	cd /home/icubuser/mc/install/Tasks/build/binding/python && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/icubuser/mc/install/Tasks/build/binding/python/tasks.cpp -o CMakeFiles/_tasks.dir/tasks.cpp.s

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.requires:

.PHONY : binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.requires

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.provides: binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.requires
	$(MAKE) -f binding/python/CMakeFiles/_tasks.dir/build.make binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.provides.build
.PHONY : binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.provides

binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.provides.build: binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o


# Object files for target _tasks
_tasks_OBJECTS = \
"CMakeFiles/_tasks.dir/tasks.cpp.o"

# External object files for target _tasks
_tasks_EXTERNAL_OBJECTS =

binding/python/tasks/_tasks.so: binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o
binding/python/tasks/_tasks.so: binding/python/CMakeFiles/_tasks.dir/build.make
binding/python/tasks/_tasks.so: src/libTasks.so.0.9.0
binding/python/tasks/_tasks.so: /usr/lib/x86_64-linux-gnu/libboost_timer.so
binding/python/tasks/_tasks.so: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
binding/python/tasks/_tasks.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
binding/python/tasks/_tasks.so: binding/python/CMakeFiles/_tasks.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/icubuser/mc/install/Tasks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library tasks/_tasks.so"
	cd /home/icubuser/mc/install/Tasks/build/binding/python && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/_tasks.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
binding/python/CMakeFiles/_tasks.dir/build: binding/python/tasks/_tasks.so

.PHONY : binding/python/CMakeFiles/_tasks.dir/build

binding/python/CMakeFiles/_tasks.dir/requires: binding/python/CMakeFiles/_tasks.dir/tasks.cpp.o.requires

.PHONY : binding/python/CMakeFiles/_tasks.dir/requires

binding/python/CMakeFiles/_tasks.dir/clean:
	cd /home/icubuser/mc/install/Tasks/build/binding/python && $(CMAKE_COMMAND) -P CMakeFiles/_tasks.dir/cmake_clean.cmake
.PHONY : binding/python/CMakeFiles/_tasks.dir/clean

binding/python/CMakeFiles/_tasks.dir/depend:
	cd /home/icubuser/mc/install/Tasks/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/icubuser/mc/install/Tasks /home/icubuser/mc/install/Tasks/binding/python /home/icubuser/mc/install/Tasks/build /home/icubuser/mc/install/Tasks/build/binding/python /home/icubuser/mc/install/Tasks/build/binding/python/CMakeFiles/_tasks.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : binding/python/CMakeFiles/_tasks.dir/depend
