
# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Define the source files
SRCS = main.cpp error/error.cpp

# Define the output binary
TARGET = lox

# Define the object files (derived from the source files)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the project
all: $(TARGET)
	@./$(TARGET)

# Rule to build the target binary
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the object files
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	@rm -f $(OBJS) $(TARGET)

.PHONY: all clean

