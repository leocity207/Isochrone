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
configure_file(${PROJECT_SOURCE_DIR}/includes/config/config.h.in ${PROJECT_SOURCE_DIR}/includes/config/config.h)

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
target_sources(log PRIVATE ${PROJECT_SOURCE_DIR}/includes/config/config.cpp)

#------------------------------------
# subdirectory include
add_subdirectory(src/network)
add_subdirectory(src/utils)
add_subdirectory(src/algorithm)
add_subdirectory(src/resource/csv)
add_subdirectory(src/resource/json)




#tests
add_subdirectory(src/utils/test)
add_subdirectory(src/resource/test)
add_subdirectory(src/network/test)
add_subdirectory(src/algorithm/test)
