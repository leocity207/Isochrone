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
find_package(Doxygen REQUIRED)

# Find all the public headers
get_target_property(ISOCHRONE_PUBLIC_HEADER_DIR Isochrone INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE ISOCHRONE_PUBLIC_HEADERS ${ISOCHRONE_PUBLIC_HEADER_DIR}/*.h)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/Isochrone)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/documentation/build/doxygen)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${CAT_CUTIFIER_PUBLIC_HEADERS}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
