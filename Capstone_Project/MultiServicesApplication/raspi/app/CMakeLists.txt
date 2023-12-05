cmake_minimum_required(VERSION 3.0)
project(DaemonLogger)

# Cross-compiler setup
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER "/home/sherif/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "/home/sherif/x-tools/aarch64-rpi4-linux-gnu/bin/aarch64-rpi4-linux-gnu-g++")

# Set the path to the cross-compiled Boost libraries
set(BOOST_ROOT "/home/sherif/Desktop/MultiServicesApplication/raspi/lib/boost_1_83_0/stage/lib")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

# Find Boost libraries
find_package(Boost 1.74.0 COMPONENTS log log_setup system thread REQUIRED)

# Find the MsgQueue_lib library
find_library(MsgQueue_lib NAMES MsgQueue_lib.so HINTS "/home/sherif/Desktop/MultiServicesApplication/raspi/lib/MsgQueue_lib" REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS} "/home/sherif/Desktop/MultiServicesApplication/raspi/lib/MsgQueue_lib")

# Link directories
link_directories(${Boost_LIBRARY_DIRS})

message(STATUS "Boost Include: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost Libraries: ${Boost_LIBRARIES}")

add_library(boostLogger boostLogger.cpp)
add_library(MsgQueue_lib SHARED IMPORTED) # Assuming MsgQueue_lib is a shared library
set_property(TARGET MsgQueue_lib PROPERTY IMPORTED_LOCATION "/home/sherif/Desktop/MultiServicesApplication/raspi/lib/MsgQueue_lib/MsgQueue_lib.so")

target_link_libraries(boostLogger ${Boost_LIBRARIES} pthread rt)

add_executable(math_app math_app.cpp)
target_link_libraries(math_app boostLogger MsgQueue_lib)
#-----------------------------------------------------------
#add_executable(math_app math_app.cpp)
#add_executable(print_app print_app.cpp)
#add_executable(count_app count_app.cpp)
#target_link_libraries(math_app boostLogger)
#target_link_libraries(math_app MsgQue_lib)
#target_link_libraries(print_app boostLogger)
#target_link_libraries(print_app MsgQue_lib)
#target_link_libraries(count_app boostLogger)
#target_link_libraries(count_app MsgQue_lib)
#-----------------------------------------------------------

# Set the target properties for cross-compilation
set_target_properties(math_app PROPERTIES COMPILE_FLAGS "-march=armv8-a")
set_target_properties(math_app PROPERTIES INSTALL_RPATH "/home/sherif/Desktop/MultiServicesApplication/raspi/lib")

