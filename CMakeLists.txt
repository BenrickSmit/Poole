cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project("Poole_Test")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra ")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX ")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} -pg")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pthread")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Poole_Test src/main.cpp include/Poole/Poole.h include/Poole/Poole.cpp)