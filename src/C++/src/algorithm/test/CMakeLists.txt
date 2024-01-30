#////////////////////////
# For google test includes
include(GoogleTest)

get_filename_component(TEST_DIR ./ ABSOLUTE)

configure_file(${PROJECT_SOURCE_DIR}/src/algorithm/test/config.h.in ${PROJECT_SOURCE_DIR}/src/algorithm/test/config.h)


#/////////////////////////////////////////////////
# Glob files for adding header file to the target
file(GLOB_RECURSE MY_HEADERS "*.h")

#/////////////////////////////////////////////////
# Add all the File for the target
add_executable( algorithm_test 
    algorithm_station_test.cpp
    network_optimizer_test.cpp

    ${MY_HEADERS}
)

#/////////////////////////////////////////////////
# add header directory
target_include_directories( network_optimizer_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}                 
)


#/////////////////////////////////////
# Special compilation option for googletest
if (MSVC)
    target_compile_options(network_optimizer_test PRIVATE /W0 -/WX)
else()
    target_compile_options(network_optimizer_test PRIVATE -Wall -Wextra -pedantic -Og)
endif()


#/////////////////////////////////
#final link of the library
target_link_libraries(
  algorithm_test
  algorithm
  GTest::gtest_main
  network_optimizer
  utils
  log
  algorithm
  csv
)


gtest_discover_tests(algorithm_test)