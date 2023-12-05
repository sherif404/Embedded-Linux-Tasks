cmake_minimum_required(VERSION 3.12)
project(Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add boost and gtest libraries
find_package(Boost REQUIRED COMPONENTS log)
find_package(GTest REQUIRED)

# Include directorie
include_directories(${Boost_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

# File Handler executable
add_executable(fh 
    fh/FileHandler.cpp
    fh/NamedPipe.cpp
    fh/SharedMemory.cpp
)

target_link_libraries(fh ${Boost_LIBRARIES})

# Requester executable
add_executable(requester
    Requester/Requester.cpp
    Requester/NamedPipe.cpp
    Requester/SharedMemory.cpp
)

target_link_libraries(requester ${Boost_LIBRARIES})

# Testing executable
add_executable(tests 
    #Tests/tests.cpp
    Tests/NamedPipe.cpp
    Tests/SharedMemory.cpp
)


# Link against the Google Test library
target_link_libraries(tests  ${GTEST_BOTH_LIBRARIES})
target_link_libraries(tests  pthread)

# Link boost libraries
link_directories(${Boost_LIBRARY_DIRS})

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Log directory for Boost logger
add_definitions(-DBOOST_LOG_DYN_LINK)
set(BOOST_LOG_DYN_LINK 1)
set(BOOST_LOG_DIR ${CMAKE_BINARY_DIR}/log)

# Create log directory if it doesn't exist
if(NOT EXISTS ${BOOST_LOG_DIR})
    file(MAKE_DIRECTORY ${BOOST_LOG_DIR})
endif()

# Set log file path
add_definitions(-DLOG_FILE_PATH="${BOOST_LOG_DIR}/run_logs.txt")
