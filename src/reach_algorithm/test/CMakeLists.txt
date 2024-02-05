#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////////////////////////////////////////////
# create configuration file to find test resource path
get_filename_component(TEST_DIR ./ ABSOLUTE)
configure_file(${PROJECT_SOURCE_DIR}/src/reach_algorithm/test/config.h.in ${PROJECT_SOURCE_DIR}/src/reach_algorithm/test/config.h)


#/////////////
# SOURCE FILES
file(GLOB_RECURSE REACH_ALGORITHM_TEST_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( reach_algorithm_test 
	${REACH_ALGORITHM_TEST_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(reach_algorithm_test
	algorithm
	GTest::gtest_main
	network
	context
	utils
	log
	csv
	archive
)

#/////////////
# DECLARE TEST
gtest_discover_tests(reach_algorithm_test)