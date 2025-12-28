#!/usr/bin/env bash
##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it.

## Read the filename from the chosen location
PROJECT_NAME=$(cat build_info/build_name.txt)

# Determine the build type (Debug, Release, etc.)
BUILD_TYPE="Debug" # Default to Debug

# Construct the expected name for the test executable
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    TEST_EXECUTABLE_NAME="${PROJECT_NAME}_tests.exe"
else
    TEST_EXECUTABLE_NAME="${PROJECT_NAME}_tests"
fi

# Search for the test executable in the build directory
TEST_EXECUTABLE_PATH=$(find ./build -name "${TEST_EXECUTABLE_NAME}" -type f 2>/dev/null | grep "${BUILD_TYPE}" | head -n 1)

if [ -z "${TEST_EXECUTABLE_PATH}" ]; then
    echo "Error: Test executable not found. Tried searching for ${TEST_EXECUTABLE_NAME} in ./build/${BUILD_TYPE}/ or similar."
    exit 1
fi

echo "Running tests: ${TEST_EXECUTABLE_PATH}"
export PATH=$PATH:$(pwd)/build/bin/Debug # Add the directory containing DLLs to PATH
"${TEST_EXECUTABLE_PATH}"