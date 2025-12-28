#!/usr/bin/env bash
##-------------------------------------------------------------------------------------------------
## HEADER INFORMATION
##-------------------------------------------------------------------------------------------------
## This Shell Script is used to obtain the program filename from build_name.txt in build_info
## after which it will execute it with gprof, profiling the program for heatmaps.


##-------------------------------------------------------------------------------------------------
## SECTION: FUNCTION DECLARATIONS
##-------------------------------------------------------------------------------------------------
have_prog() {
    command -v "$1" >/dev/null 2>&1
}


##-------------------------------------------------------------------------------------------------
## SECTION: PROGRAM LOGIC
##-------------------------------------------------------------------------------------------------
PROJECT_NAME=$(cat build_info/build_name.txt)
PROJECT_VERSION=$(cat build_info/build_version.txt)
RED=`tput setaf 1`
GREEN=`tput setaf 10`
NC=`tput sgr0`

# Determine the build type (Debug, Release, etc.)
BUILD_TYPE="Debug" # Default to Debug

# Construct the expected path for the executable
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    EXECUTABLE_NAME="${PROJECT_NAME}.exe"
else
    EXECUTABLE_NAME="${PROJECT_NAME}"
fi

# Search for the executable in the build directory
EXECUTABLE_PATH=$(find ./build -name "${EXECUTABLE_NAME}" -type f 2>/dev/null | grep "${BUILD_TYPE}" | head -n 1)

if [ -z "${EXECUTABLE_PATH}" ]; then
    echo "Error: Executable not found. Tried searching for ${EXECUTABLE_NAME} in ./build/${BUILD_TYPE}/ or similar."
    exit 1
fi

if have_prog gprof ; then
    # Run gprof on the program created
    echo "Running application for profiling..."
    "${EXECUTABLE_PATH}"

    ## Determine whether the gmon.out file exists
    if [ -e "gmon.out" ]; then # gmon.out is usually created in the directory where the executable was run
        gprof "${EXECUTABLE_PATH}" gmon.out --brief > "${PROJECT_NAME}_profile_info.txt"
        cat "${PROJECT_NAME}_profile_info.txt"
    else
        echo "${RED}Profile Information Does NOT Exist. ${NC}"
        echo "${RED}Ensure the executable was compiled with profiling enabled (-pg flag) and run successfully to generate gmon.out.${NC}"
        echo "${RED}Continuing...${NC}"
    fi
else
    echo "${RED}gprof (GNU Profiler) is not installed or not in PATH.${NC}"
    echo "${RED}This profiling script is designed for Linux environments with gprof.${NC}"
    echo "${RED}For Windows, consider using Visual Studio's built-in profiler or other tools.${NC}"
fi

