# ------------------
# Compiler and Flags
# ------------------
CXX = g++
# CXXFLAGS:
# -std=c++17: Use the C++17 standard.
# -Wall -Wextra: Enable all and extra warnings. Highly recommended.
# -g: Include debug symbols in the executable for use with gdb.
# -MMD -MP: Generate dependency files (.d) to track header changes.
CXXFLAGS = -std=c++17 -Wall -Wextra -g -MMD -MP

# -----------------
# Project Structure
# -----------------
# The name of your final executable
TARGET = gb-emulator

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Automatically find all .cpp files in the source directory and its subdirectories
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Generate object file names from source file names (e.g., src/main.cpp -> src/main.o)
OBJS = $(SRCS:.cpp=.o)

# Generate dependency file names from object files (e.g., src/main.o -> src/main.d)
DEPS = $(OBJS:.o=.d)

# Include path for the compiler
INCLUDES = -I$(INCLUDE_DIR)

# ---------------
# Build Targets
# ---------------

# The default target, called when you just run "make"
all: $(TARGET)

# Rule to link all object files into the final executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile a .cpp file into a .o file
# It uses the source files found automatically
# $< is the source file name (e.g., src/main.cpp)
# $@ is the target file name (e.g., src/main.o)
%.o: %.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Include the generated dependency files.
# The hyphen before "include" tells make to ignore errors if the file doesn't exist.
-include $(DEPS)


# --------------
# Phony Targets
# --------------
.PHONY: all clean run

# Target to remove all generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(OBJS) $(DEPS)

# A convenience target to build and run the emulator
# NOTE: You must provide a valid ROM file path!
run: all
	@echo "Running emulator..."
	./$(TARGET) roms/Tetris.gb