# Compiler settings
CXX = g++
CXXFLAGS = -g -Iinclude  # Compiler flags: Enable debug and include headers from 'include/'
MINGW_CXX = x86_64-w64-mingw32-g++  # MinGW compiler for Windows
MINGW_CXXFLAGS = -g -Iinclude  # Windows compiler flags

# Source files and output binary paths
SRCDIR = src
BINDIR = bin
TARGET_LINUX = $(BINDIR)/AutoLeech_x64_Linux
TARGET_WINDOWS = $(BINDIR)/AutoLeech_x64_Windows.exe

# Find all .cpp files recursively in src/ and its subdirectories
SRC = $(shell find $(SRCDIR) -name '*.cpp')
OBJ = $(SRC:.cpp=.o)

# Default target (Linux binary)
all: $(TARGET_LINUX)

# Linux build target
$(TARGET_LINUX): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET_LINUX)

# Windows build target (using MinGW cross-compiler)
windows: $(OBJ)
	@mkdir -p $(BINDIR)
	$(MINGW_CXX) $(MINGW_CXXFLAGS) $(OBJ) -o $(TARGET_WINDOWS)

# Rule to compile .cpp files into .o object files for both platforms
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove object files and binaries
clean:
	rm -rf $(BINDIR)/*.o $(TARGET_LINUX) $(TARGET_WINDOWS)

.PHONY: all windows clean
