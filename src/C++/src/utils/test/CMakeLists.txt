#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////
# Glob files for adding header file to the target
file(GLOB_RECURSE MY_HEADERS "*.h")

#/////////////////////////////////////////////////
# Add all the File for the target
add_executable( utils_test 
    main.cpp
    coordinate_2d_test.cpp
    daytime_test.cpp
    general_test.cpp

    ${MY_HEADERS}
)

#/////////////////////////////////////////////////
# add header directory
target_include_directories( utils_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}                 
)


#/////////////////////////////////////
# Special compilation option for googletest
if (MSVC)
    target_compile_options(utils_test PRIVATE /W0 -/WX)
else()
    target_compile_options(utils_test PRIVATE -Wall -Wextra -pedantic -Og)
endif()


#/////////////////////////////////
#final link of the library
target_link_libraries(
  utils_test
  GTest::gtest_main
  utils
  log
)


