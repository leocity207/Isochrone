#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////
# SOURCE FILES
file(GLOB RESOURCE_TEST_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( ressource_test 
	${RESOURCE_TEST_SOURCE}
)

#////////////////
# EXECUTABLE LINK
target_link_libraries( ressource_test
	GTest::gtest_main
	csv
	json
	utils
	network_optimizer
	algorithm
	log
)

#/////////////
# DECLARE TEST
gtest_discover_tests(ressource_test)