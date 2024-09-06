
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LDFLAGS = -lfmt

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Finding all .cpp files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Mapping .cpp files to .o files in the object directory
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/lox

.PHONY: all clean

# Default target to build the executable
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Compiling each .cpp file into a corresponding .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the object and binary directories exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

