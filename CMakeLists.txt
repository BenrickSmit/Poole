##------------------------------------------------------------------------------
## SECTION: Set Variables
##------------------------------------------------------------------------------
## Set some settings for the builder
set(BOOL_CREATE_TESTS ON)
set(BOOL_CREATE_EXECUTABLE ON)
set(BOOL_CREATE_LIBRARY OFF)

## Obtain the project's base name and version number
file(STRINGS "build_info/build_name.txt" STRING_PROJECT_NAME)
file(STRINGS "build_info/build_version.txt" STRING_PROJECT_VERSION)

## Basic CMAKE Project Settings
cmake_minimum_required (VERSION 3.15 FATAL_ERROR)
project(${STRING_PROJECT_NAME} VERSION "${STRING_PROJECT_VERSION}")

##------------------------------------------------------------------------------
## SECTION: Add the required files to source
##------------------------------------------------------------------------------
## Add the source files to the executable
include_directories(includes)
include_directories(lib)
add_subdirectory(src)

##------------------------------------------------------------------------------
## SECTION: Enable testing on the project
##------------------------------------------------------------------------------
if(${BOOL_CREATE_TESTS})
    ## Enable Testing of the Program
    enable_testing()

    ## Add the Google Test (gtest) unit testing framework
    add_subdirectory(lib/googletest-release-1.10.0 EXCLUDE_FROM_ALL)
    ## Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    ## Add the Unit Tests
    add_subdirectory(tests)
endif()

##-----------------------------------------------------------------------------=
## SECTION: Create Bin directory
##------------------------------------------------------------------------------
file(MAKE_DIRECTORY bin)