#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poole::Poole_lib" for configuration "Release"
set_property(TARGET Poole::Poole_lib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Poole::Poole_lib PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/Poole_lib.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/Poole_lib.dll"
  )

list(APPEND _cmake_import_check_targets Poole::Poole_lib )
list(APPEND _cmake_import_check_files_for_Poole::Poole_lib "${_IMPORT_PREFIX}/lib/Poole_lib.lib" "${_IMPORT_PREFIX}/bin/Poole_lib.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
