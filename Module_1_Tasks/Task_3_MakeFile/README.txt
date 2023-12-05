# Creating-a-simple-Makefile

##  Makefile for Building and Installing Application

This Makefile automates the build process of a C++ application from a `main.cpp` source file. It includes targets for building, cleaning, and installing the application. It also supports automatic dependency tracking.

### Variables:

- `CXX`: The C++ compiler executable.
- `CXXFLAGS`: Compilation flags, including C++11 standard and Wall warnings.

### Directories:

- `SRCDIR`: Directory where the source files are located.
- `BUILDDIR`: Directory for build artifacts.
- `INSTALLDIR`: Directory for installing the binary.

### Targets:

- `all`: Builds the application by compiling `main.cpp` into an executable.
- `clean`: Removes generated build artifacts.
- `install`: Installs the compiled binary into a designated installation directory.

### Usage:

1. Clone or download this repository.
2. Place your `main.cpp` source file in the same directory as the Makefile.
3. Open a terminal and navigate to the repository directory.
4. Run `make` to build the application.
5. Run `make clean` to remove build artifacts.
6. Run `make install` to install the binary into the installation directory.

Customize the Makefile variables and structure as needed to suit your project's requirements. The Makefile also automatically handles dependency tracking to recompile when necessary.


