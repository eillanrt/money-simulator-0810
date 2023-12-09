#!/bin/bash

# Compile the C++ code
g++ main.cpp -o main.exe -lstdc++

# Check for compilation errors
if [ $? -ne 0 ]; then
  echo "Error: Compilation failed!"
  exit 1
fi

# Run the compiled program
./main.exe
