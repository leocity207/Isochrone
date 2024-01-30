#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////
# Glob files for adding header file to the target
file(GLOB_RECURSE src "*.cpp")

#/////////////////////////////////////////////////
# Add all the File for the target
add_executable( ressource_test 
    ${src}
)

#/////////////////////////////////////////////////
# add header directory
target_include_directories( ressource_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}                 
)


#/////////////////////////////////////
# Special compilation option for googletest
if (MSVC)
    target_compile_options(ressource_test PRIVATE /W0 -/WX)
else()
    target_compile_options(ressource_test PRIVATE -Wall -Wextra -pedantic -Og)
endif()


#/////////////////////////////////
#final link of the library
target_link_libraries(ressource_test
  GTest::gtest_main
  csv
  json
  utils
  network_optimizer
  algorithm
  log
)


gtest_discover_tests(ressource_test)