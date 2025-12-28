#!/usr/bin/env bash
##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it.

## Read the filename from the chosen location
SOURCE_FILENAME="${PWD}/build_info/build_name.txt"
PROJECT_NAME=$(cat build_info/build_name.txt)
PROJECT_VERSION=$(cat build_info/build_version.txt)

# Determine the build type (Debug, Release, etc.)
# This is usually set by the user or build system, we'll try to guess based on common cmake defaults
# Or, assume 'Debug' for development scripts
BUILD_TYPE="Debug" # Default to Debug

# Construct the expected path for the executable
# On Windows, executables have .exe extension. On Linux, they usually don't.
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    EXECUTABLE_NAME="${PROJECT_NAME}.exe"
else
    EXECUTABLE_NAME="${PROJECT_NAME}"
fi

# Search for the executable in the build directory
# This assumes a structure like build/<BUILD_TYPE>/<PROJECT_NAME>.exe
EXECUTABLE_PATH=$(find ./build -name "${EXECUTABLE_NAME}" -type f 2>/dev/null | grep "${BUILD_TYPE}" | head -n 1)

if [ -z "${EXECUTABLE_PATH}" ]; then
    echo "Error: Executable not found. Tried searching for ${EXECUTABLE_NAME} in ./build/${BUILD_TYPE}/ or similar."
    exit 1
fi

echo "Running: ${EXECUTABLE_PATH}"
"${EXECUTABLE_PATH}"