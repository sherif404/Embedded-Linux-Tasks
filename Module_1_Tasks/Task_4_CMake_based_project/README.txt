# Creating-a-CMake-based-project
Description:

This repository contains a CMake-based project that demonstrates the usage of static libraries and executable linking. The project includes a static library, an executable, and various source/header files.

## Project Structure

The project directory structure is as follows:

project_dir
├── include
│ ├── WriteInFile.h
│ └── Print.h
├── src
│ ├── main.cpp
│ └── Print.cpp
└── library
└── WriteInFile.cpp


# code-explanation

- The `include` directory contains the header files for the project.
- The `src` directory contains the source files for the main executable.
- The `library` directory contains the source file for the static library.

## Build and Execution

To build the project, follow these steps:

1. Make sure you have CMake installed on your system.
2. Clone this repository to your local machine.
3. Navigate to the project directory.
4. Create a build directory: `mkdir build && cd build`.
5. Generate the build files using CMake: `cmake ..`.
6. Build the project: `make`.

After successfully building the project, you can run the executable as follows:

- `./program -c` : Prints "helloWorld" on the console.
- `./program -f` : Creates a "helloWorld.txt" file and writes "helloWorld" in it.

## Dependencies

This project has the following dependencies:

- CMake (minimum version 3.12)
- C++11-compatible compiler (e.g., GCC, Clang)



