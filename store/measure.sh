#!/bin/bash

# Function to measure compile time, program size, and run time
measure() {
    target=$1
    echo "Measuring $target"
    
    # Measure compile time
    /usr/bin/time -f "Compile time: %e seconds" make $target
    
    # Measure program size
    size=$(stat -c%s "${EXE}_${target}")
    echo "Program size: $size bytes"
    
    # Measure run time
    /usr/bin/time -f "Run time: %e seconds" ./${EXE}_${target}
    echo ""
}

# Clean previous builds
make clean

# Executable name
EXE="main"

# Measure for each optimization level
measure O0
measure O1
measure O2
measure O3
measure Os

