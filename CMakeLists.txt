cmake_minimum_required(VERSION 3.10)
project(IPParser)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Add executable for the main program
add_executable(IPParser src/main.cpp src/IPParser.cpp)

# Find Boost library
find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

# Add executable for the tests
add_executable(runTests tests/test_IPParser.cpp src/IPParser.cpp)

target_link_libraries(runTests ${Boost_LIBRARIES})