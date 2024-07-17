CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

SRCS = main.cpp error/error.cpp scanner/scanner.cpp token/token.cpp utils/util.cpp parser/parser.cpp

TEST_SRCS = tests/parser-test.cpp tests/ast-test.cpp tests/scanner-test.cpp error/error.cpp scanner/scanner.cpp token/token.cpp utils/util.cpp parser/parser.cpp 
#parser/parser.cpp

TARGET = lox

TEST_TARGET = run_tests

# Define the object files (derived from the source files)
OBJS = $(SRCS:.cpp=.o)

# Define the test object files
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build the object files
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Rule to run tests
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

.PHONY: all clean test
