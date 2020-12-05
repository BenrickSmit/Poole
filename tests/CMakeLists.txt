##------------------------------------------------------------------------------
## SECTION: add unit tests
##------------------------------------------------------------------------------
set(TEST_PROJECT_NAME "${PROJECT_NAME}_tests")

## Find a list of all files in the current CMake Directory
file(GLOB_RECURSE TEST_FILE_SOURCES LIST_DIRECTORIES false *.h *.cpp)

## Add the header and src files to be compiled
#file(GLOB_RECURSE HEADER_FILE_SOURCES CMAKE_CONFIGURE_DEPENDS LIST_DIRECTORIES false "../includes/*.h")
file(GLOB_RECURSE HEADER_SRC_FILE_SOURCES CMAKE_CONFIGURE_DEPENDS LIST_DIRECTORIES false "../src/*.cpp" "../src/*.c")

set(TEST_FILE_SOURCES ${TEST_FILE_SOURCES} ${HEADER_FILE_SOURCES} ${HEADER_SRC_FILE_SOURCES})
list(REMOVE_DUPLICATES TEST_FILE_SOURCES)

## Remove the main.cpp from the list of files
set(MAIN_CPP_INDEX -1)
list(FIND TEST_FILE_SOURCES "${CMAKE_SOURCE_DIR}/tests/../src/main.cpp" MAIN_CPP_INDEX)
list(REMOVE_AT TEST_FILE_SOURCES ${MAIN_CPP_INDEX})
list(FIND TEST_FILE_SOURCES "${CMAKE_SOURCE_DIR}/tests/../src/main.cpp" MAIN_CPP_INDEX)
message(">> INDEX: ${MAIN_CPP_INDEX}")

#add_executable(${TEST_PROJECT_NAME} tests_main.cpp)
add_executable(${TEST_PROJECT_NAME} ${TEST_FILE_SOURCES})
## Find the Header And Source files to test
target_include_directories(${TEST_PROJECT_NAME} PRIVATE ../includes/ )
target_include_directories(${TEST_PROJECT_NAME} PRIVATE ../src/ )


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

