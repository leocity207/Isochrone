#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////////
# create configuration file to find test resource path
get_filename_component(TEST_DIR ./ ABSOLUTE)
configure_file(${PROJECT_SOURCE_DIR}/src/algorithm/test/config.h.in ${PROJECT_SOURCE_DIR}/src/algorithm/test/config.h)


#/////////////
# SOURCE FILES
file(GLOB_RECURSE ALGORITHM_TEST_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( algorithm_test 
	${ALGORITHM_TEST_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(algorithm_test
  algorithm
  GTest::gtest_main
  network_optimizer
  utils
  log
  algorithm
  csv
)

#/////////////
# DECLARE TEST
gtest_discover_tests(algorithm_test)