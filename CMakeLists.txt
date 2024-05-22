cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 1.0.${PATCH_VERSION})

project(IPParser VERSION ${PROJECT_VERSION})

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

SET(Boost_USE_STATIC_LIBS OFF)
IF( WIN32 )
    # The auto-linking feature has problems with USE_STATIC_LIBS off, so we use
    # BOOST_ALL_NO_LIB to turn it off.
    # Several boost libraries headers aren't configured correctly if
    # USE_STATIC_LIBS is off, so we explicitly say they are dynamic with the
    # remaining definitions.
    ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB -DBOOST_PROGRAM_OPTIONS_DYN_LINK -DBOOST_IOSTREAMS_DYN_LINK -DBOOST_THREAD_DYN_LINK)
ENDIF( )

# Include directories
include_directories(include)

# Add executable for the main program
add_executable(IPParser src/main.cpp src/IPParser.cpp)

# Find Boost library
find_package(Boost 1.65 REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
target_link_libraries(runTests LINK_PUBLIC ${Boost_LIBRARIES})

# Add executable for the tests
add_executable(runTests tests/test_IPParser.cpp src/IPParser.cpp)

# CParck configuration
set(CPACK_GENERATOR "NSIS;ZIP")
set(CPACK_PACKAGE_NAME "IPParser")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")

include(CPack)

enable_testing()

add_test(runTests runTests)