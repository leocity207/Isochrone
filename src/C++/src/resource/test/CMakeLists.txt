#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////
# Glob files for adding header file to the target
file(GLOB_RECURSE MY_HEADERS "*.h")

#/////////////////////////////////////////////////
# Add all the File for the target
add_executable( csv_test 
    main.cpp
    csv_schedule_test.cpp
    csv_station_test.cpp
    resource_getter_test.cpp

    ${MY_HEADERS}
)

#/////////////////////////////////////////////////
# add header directory
target_include_directories( csv_test PRIVATE 
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
target_link_libraries(csv_test
  GTest::gtest_main
  csv
  utils
  network_optimizer
  algorithm
  log
)


