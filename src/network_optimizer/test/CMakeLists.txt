#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////
# SOURCE FILES
file(GLOB NETWORK_OPTIMIZER_TEST_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( network_optimizer_test 
	${NETWORK_OPTIMIZER_TEST_SOURCE}
)

#////////////////
# EXECUTABLE LINK
target_link_libraries( network_optimizer_test
  GTest::gtest_main
  network_optimizer
  utils
  log
  algorithm
)

#/////////////
# DECLARE TEST
gtest_discover_tests(network_optimizer_test)