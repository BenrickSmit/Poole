#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poole::Poole_lib" for configuration "Debug"
set_property(TARGET Poole::Poole_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Poole::Poole_lib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/Poole_lib.lib"
  )

list(APPEND _cmake_import_check_targets Poole::Poole_lib )
list(APPEND _cmake_import_check_files_for_Poole::Poole_lib "${_IMPORT_PREFIX}/lib/Poole_lib.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
