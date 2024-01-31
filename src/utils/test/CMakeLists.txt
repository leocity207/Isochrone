#////////////////////////
# For google test includes
include(GoogleTest)

#/////////////
# SOURCE FILES
file(GLOB UTILS_TEST_SOURCES "./*.cpp")

#///////////
# EXECUTABLE
add_executable( utils_test 
	${UTILS_TEST_SOURCES}
)

#////////////////
# EXECUTABLE LINK
target_link_libraries( utils_test
	GTest::gtest_main
	utils
	log
)

#/////////////
# DECLARE TEST
gtest_discover_tests(utils_test)
