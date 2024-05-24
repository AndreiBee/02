cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 1.0.${PATCH_VERSION})

project(IPParser VERSION ${PROJECT_VERSION})

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

SET(Boost_USE_STATIC_LIBS ON)
# IF( WIN32 )
    # The auto-linking feature has problems with USE_STATIC_LIBS off, so we use
    # BOOST_ALL_NO_LIB to turn it off.
    # Several boost libraries headers aren't configured correctly if
    # USE_STATIC_LIBS is off, so we explicitly say they are dynamic with the
    # remaining definitions.
#     ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB -DBOOST_PROGRAM_OPTIONS_DYN_LINK -DBOOST_IOSTREAMS_DYN_LINK -DBOOST_THREAD_DYN_LINK)
# ENDIF( )

# Include directories
include_directories(include)

# Add executable for the main program
add_executable(IPParser src/main.cpp src/IPParser.cpp)

# Find Boost library
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Add executable for the tests
add_executable(runTests tests/test_IPParser.cpp src/IPParser.cpp)

message(STATUS "Boost_UNIT_TEST_FRAMEWORK_LIBRARY: ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}")

if( WIN32 )
    target_link_libraries(runTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
    target_link_libraries(runTests LINK_PUBLIC ${Boost_LIBRARIES})
endif( WIN32 )
# ${Boost_FILESYSTEM_LIBRARY}
# ${Boost_SYSTEM_LIBRARY}

# Define the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include NSIS packaging
if(WIN32)
    find_program(NSIS_MAKENSIS_EXECUTABLE makensis)
    if(NSIS_MAKENSIS_EXECUTABLE)
        # Create an NSIS script
        set(NSIS_SCRIPT "${CMAKE_BINARY_DIR}/installer.nsi")
        configure_file(
            "${CMAKE_SOURCE_DIR}/installer.nsi.in"
            "${NSIS_SCRIPT}"
            @ONLY
        )

        # Add a custom target to create the installer
        add_custom_target(
            package
            COMMAND ${NSIS_MAKENSIS_EXECUTABLE} ${NSIS_SCRIPT}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating NSIS installer"
            VERBATIM
        )

        # Ensure the executable is built before packaging
        add_dependencies(package IPParser)
    else()
        message(WARNING "NSIS not found, installer will not be generated")
    endif()
endif()

# CPack configuration
if ( WIN32 )
    set(CPACK_GENERATOR "NSIS;ZIP")
else()
    set(CPACK_GENERATOR "DEB")
    set(CPACK_PACKAGE_NAME "IPParser")
    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
    set(CPACK_PACKAGE_CONTACT example@example.com)
    include(CPack)
endif( WIN32 )

enable_testing()

add_test(runTests runTests)