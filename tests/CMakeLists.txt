##------------------------------------------------------------------------------
## SECTION: add unit tests
##------------------------------------------------------------------------------
set(TEST_PROJECT_NAME "${PROJECT_NAME}_tests")

## Find a list of all files in the current CMake Directory
file(GLOB_RECURSE TEST_FILE_SOURCES LIST_DIRECTORIES false *.h *.cpp)
#add_executable(${TEST_PROJECT_NAME} tests_main.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILE_SOURCES})

## Add Google Test to the framework, and run all unit tests
# Google C++ Testing Framework
# https://code.google.com/p/googletest/
set(THREAD_USED pthread)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(THREAD_USED "")
endif()
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC gtest gtest_main ${THREAD_USED})

## Required to add individual tests
#add_test(GOOGLE_TEST_ALIVE_TEST ${TEST_PROJECT_NAME})

