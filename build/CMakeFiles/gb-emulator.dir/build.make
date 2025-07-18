# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Pratyush/study/GB-emulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Pratyush/study/GB-emulator/build

# Include any dependencies generated for this target.
include CMakeFiles/gb-emulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gb-emulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gb-emulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gb-emulator.dir/flags.make

CMakeFiles/gb-emulator.dir/src/cart.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cart.cpp.o: ../src/cart.cpp
CMakeFiles/gb-emulator.dir/src/cart.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gb-emulator.dir/src/cart.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cart.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cart.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cart.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cart.cpp

CMakeFiles/gb-emulator.dir/src/cart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cart.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cart.cpp > CMakeFiles/gb-emulator.dir/src/cart.cpp.i

CMakeFiles/gb-emulator.dir/src/cart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cart.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cart.cpp -o CMakeFiles/gb-emulator.dir/src/cart.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o: ../src/cpu/cpu.cpp
CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/cpu.cpp

CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/cpu.cpp > CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/cpu.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o: ../src/cpu/decode_instructions.cpp
CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/decode_instructions.cpp

CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/decode_instructions.cpp > CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/decode_instructions.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o: ../src/cpu/instructions.cpp
CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/instructions.cpp

CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/instructions.cpp > CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/instructions.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o: ../src/cpu/mmu.cpp
CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/mmu.cpp

CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/mmu.cpp > CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/mmu.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o: ../src/cpu/process_instructions.cpp
CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/process_instructions.cpp

CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/process_instructions.cpp > CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/process_instructions.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.s

CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o: ../src/cpu/registers.cpp
CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o -MF CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/cpu/registers.cpp

CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/cpu/registers.cpp > CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.i

CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/cpu/registers.cpp -o CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.s

CMakeFiles/gb-emulator.dir/src/emu.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/emu.cpp.o: ../src/emu.cpp
CMakeFiles/gb-emulator.dir/src/emu.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/gb-emulator.dir/src/emu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/emu.cpp.o -MF CMakeFiles/gb-emulator.dir/src/emu.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/emu.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/emu.cpp

CMakeFiles/gb-emulator.dir/src/emu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/emu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/emu.cpp > CMakeFiles/gb-emulator.dir/src/emu.cpp.i

CMakeFiles/gb-emulator.dir/src/emu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/emu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/emu.cpp -o CMakeFiles/gb-emulator.dir/src/emu.cpp.s

CMakeFiles/gb-emulator.dir/src/main.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/gb-emulator.dir/src/main.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/gb-emulator.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/main.cpp.o -MF CMakeFiles/gb-emulator.dir/src/main.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/main.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/main.cpp

CMakeFiles/gb-emulator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/main.cpp > CMakeFiles/gb-emulator.dir/src/main.cpp.i

CMakeFiles/gb-emulator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/main.cpp -o CMakeFiles/gb-emulator.dir/src/main.cpp.s

CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o: CMakeFiles/gb-emulator.dir/flags.make
CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o: ../src/mmu/ppu.cpp
CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o: CMakeFiles/gb-emulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o -MF CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o.d -o CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o -c /mnt/c/Pratyush/study/GB-emulator/src/mmu/ppu.cpp

CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Pratyush/study/GB-emulator/src/mmu/ppu.cpp > CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.i

CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Pratyush/study/GB-emulator/src/mmu/ppu.cpp -o CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.s

# Object files for target gb-emulator
gb__emulator_OBJECTS = \
"CMakeFiles/gb-emulator.dir/src/cart.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/emu.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/main.cpp.o" \
"CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o"

# External object files for target gb-emulator
gb__emulator_EXTERNAL_OBJECTS =

gb-emulator: CMakeFiles/gb-emulator.dir/src/cart.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/cpu.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/decode_instructions.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/instructions.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/mmu.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/process_instructions.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/cpu/registers.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/emu.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/main.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/src/mmu/ppu.cpp.o
gb-emulator: CMakeFiles/gb-emulator.dir/build.make
gb-emulator: CMakeFiles/gb-emulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable gb-emulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gb-emulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gb-emulator.dir/build: gb-emulator
.PHONY : CMakeFiles/gb-emulator.dir/build

CMakeFiles/gb-emulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gb-emulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gb-emulator.dir/clean

CMakeFiles/gb-emulator.dir/depend:
	cd /mnt/c/Pratyush/study/GB-emulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Pratyush/study/GB-emulator /mnt/c/Pratyush/study/GB-emulator /mnt/c/Pratyush/study/GB-emulator/build /mnt/c/Pratyush/study/GB-emulator/build /mnt/c/Pratyush/study/GB-emulator/build/CMakeFiles/gb-emulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gb-emulator.dir/depend

