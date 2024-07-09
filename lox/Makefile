# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Define the source files (excluding test files)
SRCS = main.cpp error/error.cpp scanner/scanner.cpp token/token.cpp utils/util.cpp

# Define the test source files
TEST_SRCS = tests/tests.cpp error/error.cpp scanner/scanner.cpp token/token.cpp utils/util.cpp

# Define the output binary
TARGET = lox

# Define the test binary
TEST_TARGET = run_tests

# Define the object files (derived from the source files)
OBJS = $(SRCS:.cpp=.o)

# Define the test object files
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default rule to build the project
all: $(TARGET)

# Rule to build the target binary
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the test binary
$(TEST_TARGET): $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build the object files
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	@rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Rule to run tests
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

.PHONY: all clean test
