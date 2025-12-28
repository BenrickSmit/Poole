@PACKAGE_INIT@

include (CMakeFindDependencyMacro)
find_dependency (Threads QUIET) # Poole depends on Threads

include ("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake")

check_required_components("@PROJECT_NAME@")