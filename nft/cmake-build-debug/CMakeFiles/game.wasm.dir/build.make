# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Volumes/sd/workspace/nft

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Volumes/sd/workspace/nft/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/game.wasm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game.wasm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.wasm.dir/flags.make

CMakeFiles/game.wasm.dir/src/game.cpp.o: CMakeFiles/game.wasm.dir/flags.make
CMakeFiles/game.wasm.dir/src/game.cpp.o: ../src/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Volumes/sd/workspace/nft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game.wasm.dir/src/game.cpp.o"
	//usr/local/bin/eosio-cpp  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.wasm.dir/src/game.cpp.o -c /Volumes/sd/workspace/nft/src/game.cpp

CMakeFiles/game.wasm.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.wasm.dir/src/game.cpp.i"
	//usr/local/bin/eosio-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Volumes/sd/workspace/nft/src/game.cpp > CMakeFiles/game.wasm.dir/src/game.cpp.i

CMakeFiles/game.wasm.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.wasm.dir/src/game.cpp.s"
	//usr/local/bin/eosio-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Volumes/sd/workspace/nft/src/game.cpp -o CMakeFiles/game.wasm.dir/src/game.cpp.s

# Object files for target game.wasm
game_wasm_OBJECTS = \
"CMakeFiles/game.wasm.dir/src/game.cpp.o"

# External object files for target game.wasm
game_wasm_EXTERNAL_OBJECTS =

game.wasm: CMakeFiles/game.wasm.dir/src/game.cpp.o
game.wasm: CMakeFiles/game.wasm.dir/build.make
game.wasm: CMakeFiles/game.wasm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Volumes/sd/workspace/nft/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable game.wasm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game.wasm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.wasm.dir/build: game.wasm

.PHONY : CMakeFiles/game.wasm.dir/build

CMakeFiles/game.wasm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game.wasm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game.wasm.dir/clean

CMakeFiles/game.wasm.dir/depend:
	cd /Volumes/sd/workspace/nft/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Volumes/sd/workspace/nft /Volumes/sd/workspace/nft /Volumes/sd/workspace/nft/cmake-build-debug /Volumes/sd/workspace/nft/cmake-build-debug /Volumes/sd/workspace/nft/cmake-build-debug/CMakeFiles/game.wasm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game.wasm.dir/depend

