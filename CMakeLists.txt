cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(GAapp VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory for header files
include_directories(include)

# Add the executable target
add_executable(main
               main.cpp
               src/GeneticAlgo.cpp
)