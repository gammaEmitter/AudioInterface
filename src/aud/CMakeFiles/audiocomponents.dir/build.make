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
include src/aud/CMakeFiles/audiocomponents.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.make

# Include the progress variables for this target.
include src/aud/CMakeFiles/audiocomponents.dir/progress.make

# Include the compile flags for this target's objects.
include src/aud/CMakeFiles/audiocomponents.dir/flags.make

src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o: src/aud/audiointerface.cpp
src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o -MF CMakeFiles/audiocomponents.dir/audiointerface.cpp.o.d -o CMakeFiles/audiocomponents.dir/audiointerface.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp

src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/audiointerface.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp > CMakeFiles/audiocomponents.dir/audiointerface.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/audiointerface.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/audiointerface.cpp -o CMakeFiles/audiocomponents.dir/audiointerface.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o: src/aud/bus.cpp
src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o -MF CMakeFiles/audiocomponents.dir/bus.cpp.o.d -o CMakeFiles/audiocomponents.dir/bus.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp

src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/bus.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp > CMakeFiles/audiocomponents.dir/bus.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/bus.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bus.cpp -o CMakeFiles/audiocomponents.dir/bus.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o: src/aud/bufferservice.cpp
src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o -MF CMakeFiles/audiocomponents.dir/bufferservice.cpp.o.d -o CMakeFiles/audiocomponents.dir/bufferservice.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp

src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/bufferservice.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp > CMakeFiles/audiocomponents.dir/bufferservice.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/bufferservice.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/bufferservice.cpp -o CMakeFiles/audiocomponents.dir/bufferservice.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o: src/aud/channel.cpp
src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o -MF CMakeFiles/audiocomponents.dir/channel.cpp.o.d -o CMakeFiles/audiocomponents.dir/channel.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp

src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/channel.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp > CMakeFiles/audiocomponents.dir/channel.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/channel.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/channel.cpp -o CMakeFiles/audiocomponents.dir/channel.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o: src/aud/ringbuffer.cpp
src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o -MF CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o.d -o CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp

src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/ringbuffer.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp > CMakeFiles/audiocomponents.dir/ringbuffer.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/ringbuffer.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/ringbuffer.cpp -o CMakeFiles/audiocomponents.dir/ringbuffer.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o: src/aud/clockbase.cpp
src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o -MF CMakeFiles/audiocomponents.dir/clockbase.cpp.o.d -o CMakeFiles/audiocomponents.dir/clockbase.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp

src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/clockbase.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp > CMakeFiles/audiocomponents.dir/clockbase.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/clockbase.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/clockbase.cpp -o CMakeFiles/audiocomponents.dir/clockbase.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o: src/aud/oscillator.cpp
src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o -MF CMakeFiles/audiocomponents.dir/oscillator.cpp.o.d -o CMakeFiles/audiocomponents.dir/oscillator.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp

src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/oscillator.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp > CMakeFiles/audiocomponents.dir/oscillator.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/oscillator.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/oscillator.cpp -o CMakeFiles/audiocomponents.dir/oscillator.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o: src/aud/wavetable.cpp
src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o -MF CMakeFiles/audiocomponents.dir/wavetable.cpp.o.d -o CMakeFiles/audiocomponents.dir/wavetable.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp

src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/wavetable.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp > CMakeFiles/audiocomponents.dir/wavetable.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/wavetable.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wavetable.cpp -o CMakeFiles/audiocomponents.dir/wavetable.cpp.s

src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/flags.make
src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o: src/aud/wtoscillator.cpp
src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o: src/aud/CMakeFiles/audiocomponents.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o -MF CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o.d -o CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o -c /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp

src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/audiocomponents.dir/wtoscillator.cpp.i"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp > CMakeFiles/audiocomponents.dir/wtoscillator.cpp.i

src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/audiocomponents.dir/wtoscillator.cpp.s"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/wtoscillator.cpp -o CMakeFiles/audiocomponents.dir/wtoscillator.cpp.s

# Object files for target audiocomponents
audiocomponents_OBJECTS = \
"CMakeFiles/audiocomponents.dir/audiointerface.cpp.o" \
"CMakeFiles/audiocomponents.dir/bus.cpp.o" \
"CMakeFiles/audiocomponents.dir/bufferservice.cpp.o" \
"CMakeFiles/audiocomponents.dir/channel.cpp.o" \
"CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o" \
"CMakeFiles/audiocomponents.dir/clockbase.cpp.o" \
"CMakeFiles/audiocomponents.dir/oscillator.cpp.o" \
"CMakeFiles/audiocomponents.dir/wavetable.cpp.o" \
"CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o"

# External object files for target audiocomponents
audiocomponents_EXTERNAL_OBJECTS =

lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/audiointerface.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/bus.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/bufferservice.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/channel.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/ringbuffer.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/clockbase.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/oscillator.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/wavetable.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/wtoscillator.cpp.o
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/build.make
lib/libaudiocomponents.a: src/aud/CMakeFiles/audiocomponents.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../../lib/libaudiocomponents.a"
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && $(CMAKE_COMMAND) -P CMakeFiles/audiocomponents.dir/cmake_clean_target.cmake
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/audiocomponents.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/aud/CMakeFiles/audiocomponents.dir/build: lib/libaudiocomponents.a
.PHONY : src/aud/CMakeFiles/audiocomponents.dir/build

src/aud/CMakeFiles/audiocomponents.dir/clean:
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud && $(CMAKE_COMMAND) -P CMakeFiles/audiocomponents.dir/cmake_clean.cmake
.PHONY : src/aud/CMakeFiles/audiocomponents.dir/clean

src/aud/CMakeFiles/audiocomponents.dir/depend:
	cd /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud /Users/franzweunsche/Desktop/Programming/cpp_proj/AudioInterface_dev/src/aud/CMakeFiles/audiocomponents.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/aud/CMakeFiles/audiocomponents.dir/depend
