cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 1.0.${PATCH_VERSION})

project(IPParser VERSION ${PROJECT_VERSION})

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

# CParck configuration
set(CPACK_GENERATOR "NSIS;ZIP")
set(CPACK_PACKAGE_NAME "IPParser")
# set(CPACK_PACKAGE_VERSION "1.0.${PATCH_VERSION}")
# set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")

include(CPack)

enable_testing()

add_test(runTests runTests)