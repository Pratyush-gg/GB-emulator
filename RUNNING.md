# How to Build and Run the Game Boy Emulator

This document provides step-by-step instructions for building and running the GB Emulator on Windows using the command line.

---

## Prerequisites

To build and run the emulator, you will need:

1. **CMake** (version 3.28 or later) installed and added to the system `PATH`.
2. **Git** installed and added to the system `PATH` (used by CMake FetchContent to download SFML, ImGui, and ImGui-SFML).
3. A C++17 compatible compiler:
   - **MSYS2 (UCRT64/MinGW)**: Provides `g++` and `mingw32-make` (Recommended).
   - *OR* **Visual Studio (MSVC)** toolchain.

---

## 1. Building with MinGW/MSYS2 (UCRT64)

To compile using GCC/MinGW via command-line (PowerShell or Command Prompt):

1. **Clear any existing build cache** (especially if you previously used CLion or Visual Studio):
   ```powershell
   Remove-Item -Recurse -Force cmake-build-debug\CMakeCache.txt, cmake-build-debug\CMakeFiles
   ```

2. **Configure the project** using the MinGW generator:
   ```powershell
   cmake -G "MinGW Makefiles" -B cmake-build-debug -S .
   ```

3. **Build the emulator** (using parallel compile jobs):
   ```powershell
   cmake --build cmake-build-debug -j
   ```

The compiled binary and dependencies (SFML DLLs, OpenAL, etc.) will be copied to `cmake-build-debug/bin/`.

---

## 2. Building with Visual Studio (MSVC)

If you prefer building a standalone native Windows binary using Visual Studio build tools:

1. **Clear any existing build cache**:
   ```powershell
   Remove-Item -Recurse -Force cmake-build-debug\CMakeCache.txt, cmake-build-debug\CMakeFiles
   ```

2. **Configure the project** (MSVC is the default generator on Windows):
   ```powershell
   cmake -B cmake-build-debug -S .
   ```

3. **Build the emulator** (specify Debug or Release configuration, using parallel compile jobs):
   ```powershell
   cmake --build cmake-build-debug --config Debug -j
   ```

---

> [!TIP]
> ### Speeding Up Builds (Incremental & Parallel Compilation)
> 1. **Do not clear the cache every time**: You only need to run the `Remove-Item` and configure `cmake -B ...` commands if you add new files, modify the `CMakeLists.txt` file, or switch compilers. If you only modify code in existing files, just run the build step. It will compile incrementally in under 2 seconds!
> 2. **Parallel compilation (`-j`)**: Passing the `-j` flag tells CMake to compile multiple files in parallel using all available CPU cores, making full cleans or first-time builds significantly faster.


---

## 3. Running the Emulator

You can run the emulator and pass a Game Boy ROM path as a command-line argument:

```powershell
# Syntax
cmake-build-debug\bin\gb-emulator.exe <path_to_rom>

# Example running Tetris
cmake-build-debug\bin\gb-emulator.exe roms/Tetris.gb

# Example running a test ROM
cmake-build-debug\bin\gb-emulator.exe roms/tests/cpu_instrs/individual/02-interrupts.gb
```

> [!NOTE]
> If you run the emulator without passing any arguments, it defaults to loading `roms/tests/cpu_instrs/individual/02-interrupts.gb`.

---

## Emulator Controls

When the emulator is running, use the following keys on the keyboard to control the game:

| Game Boy Button | Keyboard Key |
| :--- | :--- |
| **A** | `X` |
| **B** | `Z` |
| **D-Pad Up** | `Up Arrow` |
| **D-Pad Down** | `Down Arrow` |
| **D-Pad Left** | `Left Arrow` |
| **D-Pad Right** | `Right Arrow` |
| **Start** | `Enter` |
| **Select** | `Tab` |

---

## Interactive Debugger (Command Prompt)

When the debugger window opens, emulation starts in a **paused** state. You can type commands in the ImGui input box at the bottom of the debugger window to control execution:

- `c` : Continue running emulation.
- `s` : Step Into (execute one instruction).
- `n` : Step Over (step over functions/calls).
- `f` : Step Out (execute until function returns).
- `b <hex_address>` : Toggle breakpoint at the specified hexadecimal address (e.g. `b 0100`).
- `r` : Reload the ROM and restart emulation.
- `h <hex_address>` : Move the Hex Viewer panel to show memory starting at the specified address (e.g. `h C000`).
