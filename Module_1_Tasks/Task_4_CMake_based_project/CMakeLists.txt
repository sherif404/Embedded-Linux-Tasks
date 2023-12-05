cmake_minimum_required(VERSION 3.5)
project(program)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library target
add_library(WriteInFile STATIC library/WriteInFile.cpp)
target_include_directories(WriteInFile PUBLIC include)  # Include the 'include' directory

# Add the executable target
add_executable(program src/main.cpp src/Print.cpp)
target_include_directories(program PRIVATE include)  # Include the 'include' directory

# Link the executable with the library
target_link_libraries(program PRIVATE WriteInFile)
