#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////
# Glob files for adding header file to the target
file(GLOB_RECURSE MY_HEADERS "*.h")

#/////////////////////////////////////////////////
# Add all the File for the target
add_executable( network_optimizer_test 
    day_info_test.cpp
    line_test.cpp
    schedule_test.cpp
    station_test.cpp
    main.cpp

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
  network_optimizer_test
  GTest::gtest_main
  network_optimizer
  utils
  log
  algorithm
)

gtest_discover_tests(network_optimizer_test)