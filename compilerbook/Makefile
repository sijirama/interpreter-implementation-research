
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Source file and executable name
SRC = main.cpp
EXE = main

# Default target to build the executable with -O0 optimization
default: $(EXE)_O0

# Targets for different optimization levels
O0: CXXFLAGS += -O0
O1: CXXFLAGS += -O1
O2: CXXFLAGS += -O2
O3: CXXFLAGS += -O3
Os: CXXFLAGS += -Os

$(EXE)_O0: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC)

$(EXE)_O1: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE)_O1 $(SRC)

$(EXE)_O2: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE)_O2 $(SRC)

$(EXE)_O3: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE)_O3 $(SRC)

$(EXE)_Os: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXE)_Os $(SRC)

# Clean target
clean:
	rm -f $(EXE) $(EXE)_O1 $(EXE)_O2 $(EXE)_O3 $(EXE)_Os

.PHONY: clean default O0 O1 O2 O3 Os

