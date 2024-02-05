#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////
# SOURCE FILES
file(GLOB NETWORK_TEST_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( network_test 
	${NETWORK_TEST_SOURCE}
)

#////////////////
# EXECUTABLE LINK
target_link_libraries( network_test
  GTest::gtest_main
  network
  utils
  log
)

#/////////////
# DECLARE TEST
gtest_discover_tests(network_test)