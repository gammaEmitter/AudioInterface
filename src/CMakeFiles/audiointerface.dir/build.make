# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev

# Include any dependencies generated for this target.
include src/CMakeFiles/audiointerface.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/audiointerface.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/audiointerface.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/audiointerface.dir/flags.make

src/CMakeFiles/audiointerface.dir/main.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/main.cpp.o: src/main.cpp
src/CMakeFiles/audiointerface.dir/main.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/audiointerface.dir/main.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/main.cpp.o -MF CMakeFiles/audiointerface.dir/main.cpp.o.d -o CMakeFiles/audiointerface.dir/main.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/main.cpp

src/CMakeFiles/audiointerface.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/main.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/main.cpp > CMakeFiles/audiointerface.dir/main.cpp.i

src/CMakeFiles/audiointerface.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/main.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/main.cpp -o CMakeFiles/audiointerface.dir/main.cpp.s

src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o: src/aud/audiointerface.cpp
src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o -MF CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp

src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp > CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.i

src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp -o CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.s

src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o: src/aud/audioevent.cpp
src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o -MF CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audioevent.cpp

src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/audioevent.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audioevent.cpp > CMakeFiles/audiointerface.dir/aud/audioevent.cpp.i

src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/audioevent.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audioevent.cpp -o CMakeFiles/audiointerface.dir/aud/audioevent.cpp.s

src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o: src/aud/bus.cpp
src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o -MF CMakeFiles/audiointerface.dir/aud/bus.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/bus.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp

src/CMakeFiles/audiointerface.dir/aud/bus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/bus.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp > CMakeFiles/audiointerface.dir/aud/bus.cpp.i

src/CMakeFiles/audiointerface.dir/aud/bus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/bus.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp -o CMakeFiles/audiointerface.dir/aud/bus.cpp.s

src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o: src/aud/bufferservice.cpp
src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o -MF CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp

src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp > CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.i

src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp -o CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.s

src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o: src/aud/channel.cpp
src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o -MF CMakeFiles/audiointerface.dir/aud/channel.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/channel.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp

src/CMakeFiles/audiointerface.dir/aud/channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/channel.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp > CMakeFiles/audiointerface.dir/aud/channel.cpp.i

src/CMakeFiles/audiointerface.dir/aud/channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/channel.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp -o CMakeFiles/audiointerface.dir/aud/channel.cpp.s

src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o: src/aud/ringbuffer.cpp
src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o -MF CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp

src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp > CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.i

src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp -o CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.s

src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o: src/aud/clockbase.cpp
src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o -MF CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp

src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/clockbase.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp > CMakeFiles/audiointerface.dir/aud/clockbase.cpp.i

src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/clockbase.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp -o CMakeFiles/audiointerface.dir/aud/clockbase.cpp.s

src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o: src/aud/metronome.cpp
src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o -MF CMakeFiles/audiointerface.dir/aud/metronome.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/metronome.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/metronome.cpp

src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/metronome.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/metronome.cpp > CMakeFiles/audiointerface.dir/aud/metronome.cpp.i

src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/metronome.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/metronome.cpp -o CMakeFiles/audiointerface.dir/aud/metronome.cpp.s

src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o: src/aud/oscillator.cpp
src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o -MF CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp

src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/oscillator.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp > CMakeFiles/audiointerface.dir/aud/oscillator.cpp.i

src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/oscillator.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp -o CMakeFiles/audiointerface.dir/aud/oscillator.cpp.s

src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o: src/aud/resourcemanager.cpp
src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o -MF CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/resourcemanager.cpp

src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/resourcemanager.cpp > CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.i

src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/resourcemanager.cpp -o CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.s

src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o: src/aud/wavetable.cpp
src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o -MF CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp

src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/wavetable.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp > CMakeFiles/audiointerface.dir/aud/wavetable.cpp.i

src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/wavetable.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp -o CMakeFiles/audiointerface.dir/aud/wavetable.cpp.s

src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o: src/CMakeFiles/audiointerface.dir/flags.make
src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o: src/aud/wtoscillator.cpp
src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o: src/CMakeFiles/audiointerface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o -MF CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o.d -o CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp

src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp > CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.i

src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp -o CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.s

# Object files for target audiointerface
audiointerface_OBJECTS = \
"CMakeFiles/audiointerface.dir/main.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/bus.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/channel.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/metronome.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o" \
"CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o"

# External object files for target audiointerface
audiointerface_EXTERNAL_OBJECTS =

bin/audiointerface: src/CMakeFiles/audiointerface.dir/main.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/audiointerface.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/audioevent.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/bus.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/bufferservice.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/channel.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/ringbuffer.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/clockbase.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/metronome.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/oscillator.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/resourcemanager.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/wavetable.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/aud/wtoscillator.cpp.o
bin/audiointerface: src/CMakeFiles/audiointerface.dir/build.make
bin/audiointerface: lib/libtooling.a
bin/audiointerface: src/CMakeFiles/audiointerface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable ../bin/audiointerface"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audiointerface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/audiointerface.dir/build: bin/audiointerface
.PHONY : src/CMakeFiles/audiointerface.dir/build

src/CMakeFiles/audiointerface.dir/clean:
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src && $(CMAKE_COMMAND) -P CMakeFiles/audiointerface.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/audiointerface.dir/clean

src/CMakeFiles/audiointerface.dir/depend:
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/CMakeFiles/audiointerface.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/audiointerface.dir/depend

