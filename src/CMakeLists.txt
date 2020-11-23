##------------------------------------------------------------------------------
## SECTION: Setup the Source Executable
##------------------------------------------------------------------------------
set(BOOL_CREATE_INSTALLER OFF)
set(BOOL_CREATE_EXECUTABLE ON)
set(BOOL_CREATE_LIBRARY ON)
set(BOOL_PROFILE_CODE OFF)
set(BOOL_USE_BOOST OFF)

## Read the required C++ version
file(STRINGS "../build_info/build_cxx_standard.txt" STRING_REQUIRED_CXX_STANDARD)

## Find a list of all files in the current CMake Directory
file(GLOB_RECURSE EXEC_FILE_SOURCES LIST_DIRECTORIES false *.h *.cpp)

## Set the required C++ Standard
set(CMAKE_CXX_STANDARD ${STRING_REQUIRED_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Enable gprof profiling of code
if(${BOOL_PROFILE_CODE})
    #set(DCMAKE_CXX_FLAGS "${DCMAKE_CXX_FLAGS} -pg")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()



##------------------------------------------------------------------------------
## SECTION: Create an executable
##------------------------------------------------------------------------------
if(${BOOL_CREATE_EXECUTABLE})
    ## Create the required executable
    add_executable(${PROJECT_NAME} ${EXEC_FILE_SOURCES})
    
    ## If the file is successfully created, move it to bin and create a dir
    ## for the current <compiler>_<OS>_<version>
    set(EXEC_LOCATION ${CMAKE_SOURCE_DIR}/build/src/${PROJECT_NAME})
    if(EXISTS ${EXEC_LOCATION})
        ## Create the directory
        set(BASE_DIR ${CMAKE_SOURCE_DIR}/bin/exec)
        add_custom_target(build-time-make-base-exec-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${BASE_DIR})
    	set(DIR_NAME ${CMAKE_SOURCE_DIR}/bin/exec/${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME}_${PROJECT_NAME}_${PROJECT_VERSION})
    	add_custom_target(build-time-make-exec-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR_NAME})
    	
    	## Try and copy the file
    	add_custom_command(
    		TARGET ${PROJECT_NAME} POST_BUILD
    		COMMAND ${CMAKE_COMMAND} -E copy
    		${EXEC_LOCATION}
    		${DIR_NAME})
    endif()
endif()

##------------------------------------------------------------------------------
## SECTION: Create a library
##------------------------------------------------------------------------------
if(${BOOL_CREATE_LIBRARY})
    ## Create the required library
    add_library(${PROJECT_NAME}_lib STATIC ${EXEC_FILE_SOURCES})
    
    ## If the file is successfully created, move it to bin and create a dir
    ## for the current lib_<compiler>_<OS>_<version>
    set(LIB_LOCATION ${CMAKE_SOURCE_DIR}/build/src/${PROJECT_NAME}_lib)
    if(EXISTS ${LIB_LOCATION})
        ## Create the directory
        set(BASE_DIR ${CMAKE_SOURCE_DIR}/bin/libs)
        add_custom_target(build-time-make-base-lib-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${BASE_DIR})
    	set(DIR_NAME ${CMAKE_SOURCE_DIR}/bin/libs/lib_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME}_${PROJECT_NAME}_${PROJECT_VERSION})
    	add_custom_target(build-time-make-lib-directory ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR_NAME})
    	
    	## Try and copy the file
    	add_custom_command(
    		TARGET ${PROJECT_NAME}_lib POST_BUILD
    		COMMAND ${CMAKE_COMMAND} -E copy
    		${LIB_LOCATION}
    		${DIR_NAME}/)
    endif()
endif()

##------------------------------------------------------------------------------
## SECTION: Create an installer with CPack
##------------------------------------------------------------------------------
## CPack Information if you want to create an installer
if(${BOOL_CREATE_INSTALLER})
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    set(CPACK_VERBATIM_VARIABLES true)
    set(CPACK_PACKAGE_VERSION_MAJOR 0)
    set(CPACK_PACKAGE_VERSION_MINOR 1)
    set(CPACK_PACKAGE_VERSION_PATCH 0)
    #set(CPACK_PACKAGE_DESCRIPTION_SUMMARY )
    #set(CPACK_PACKAGE_DESCRIPTION_FILE )
    #set(CPACK_RESOURCE_FILE_WELCOME )
    set(CPACK_RESOURCE_FILE_LICENSE ../LICENSE)
    set(CPACK_RESOURCE_FILE_README ../README.md)
    include(CPack)
endif()

##------------------------------------------------------------------------------
## SECTION: Potential Future Version Will include
##------------------------------------------------------------------------------
#if(${BOOL_USE_BOOST})
#    set(Boost_USE_STATIC_LIBS OFF) 
#    set(Boost_USE_MULTITHREADED ON)  
#    set(Boost_USE_STATIC_RUNTIME OFF)
    
#    set(BOOST_LIBRARIES_TO_USE filesystem thread regex)
    
#    find_package(Boost 1.45.0 COMPONENTS ${BOOST_LIBRARIES_TO_USE}) 

#    if(Boost_FOUND)
#        include_directories(${Boost_INCLUDE_DIRS}) 
#        add_executable(progname file1.cxx file2.cxx) 
#        target_link_libraries(progname ${Boost_LIBRARIES})
#    endif()
#endif()
