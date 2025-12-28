##------------------------------------------------------------------------------
## SECTION: Set Variables
##------------------------------------------------------------------------------
## Set some settings for the builder
set(BOOL_CREATE_TESTS ON)
set(BOOL_CREATE_EXECUTABLE ON)
set(BOOL_CREATE_LIBRARY ON)

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
    add_subdirectory(lib/googletest-release-1.12.1 EXCLUDE_FROM_ALL)
    ## Prevent overriding the parent project's compiler/linker settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    ## Add the Unit Tests
    add_subdirectory(tests)
endif()

##-----------------------------------------------------------------------------=
## SECTION: Create Bin directory
##------------------------------------------------------------------------------
file(MAKE_DIRECTORY bin)

# Configure and install PooleConfig.cmake
install(EXPORT ${PROJECT_NAME}Targets
        FILE "${PROJECT_NAME}Targets.cmake"
        NAMESPACE "${PROJECT_NAME}::"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
install(DIRECTORY includes/ DESTINATION include)
install(FILES cmake/PooleConfig.cmake.in
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
        RENAME "${PROJECT_NAME}Config.cmake"
)

# Generate and install the version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "lib/cmake/${PROJECT_NAME}"
)