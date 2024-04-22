cmake_minimum_required(VERSION 3.22.1)

# set the project name
project(ISOCHRONE VERSION 1.0)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/includes)

#---------------------------------------
#get the current commit hash for version
execute_process(
	COMMAND git rev-parse HEAD
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_COMMIT_HASH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

#-----------------------
#setting the config file
configure_file(${PROJECT_SOURCE_DIR}/includes/config/config.h.in ${PROJECT_SOURCE_DIR}/submodule/logger/config.h)

#----------------------------------------------
# add fetch content in order to get google test
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1
)
include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#------------------------------------------
# compiler option
if (MSVC)
	# warning level 4 and all warnings as errors
	add_compile_options(/W4 /WX /utf-8)
else()
	# lots of warnings and all warnings as errors
	add_compile_options(-Wall -Wextra -pedantic -Werror -Og)
endif()

#----------------------------------------
# Subodule logger
add_subdirectory(submodule/Logger)

#------------------------------------
# subdirectory include
add_subdirectory(src/network)
add_subdirectory(src/utils)
add_subdirectory(src/reach_algorithm)
add_subdirectory(src/context)
add_subdirectory(src/resource/csv)
add_subdirectory(src/resource/json)
add_subdirectory(src/resource/archive)
add_subdirectory(src/coordinate)
add_subdirectory(src/main)



#tests
add_subdirectory(src/utils/test)
add_subdirectory(src/resource/test)
add_subdirectory(src/network/test)
add_subdirectory(src/reach_algorithm/test)
add_subdirectory(src/coordinate/test)

#-------------------------------
#Doxygen generation
# check if Doxygen is installed
find_package(Doxygen Require)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/documentation/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/documentation/build/doxygen)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/documentation
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)


#-------------------------------
# Sphinx generation
# check if Doxygen is installed
#Look for an executable called sphinx-build
find_program(SPHINX_EXECUTABLE
             NAMES sphinx-build
             DOC "Path to sphinx-build executable")

include(FindPackageHandleStandardArgs)

#Handle standard arguments to find_package like REQUIRED and QUIET
find_package_handle_standard_args(Sphinx
                                  "Failed to find sphinx-build executable"
                                  SPHINX_EXECUTABLE)
find_package(Sphinx)
if(Sphinx_FOUND)
 	FILE(GLOB SPHINX_DOC_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/documentation/source/*.rst")
	FILE(GLOB SPHINX_DOC_CODE "${CMAKE_CURRENT_SOURCE_DIR}/documentation/source/classes.rst")
    add_sphinx_document(
        Isochron_doc
        CONF_FILE "${CMAKE_CURRENT_LIST_DIR}/documentation/source/conf.py"
        ${SPHINX_DOC_MAIN}
		${SPHINX_DOC_CODE})
	add_dependencies(Isochron_doc doc_doxygen)
else()
    message(WARNING "No Sphinx found. Documentation target not available.")
endif()
