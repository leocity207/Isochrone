#/////////////
# SOURCE FILES
file(GLOB_RECURSE MAIN_SOURCE "./*.cpp")

#///////////
# EXECUTABLE
add_executable( main_app
	${MAIN_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(main_app
	reach_algorithm
	network
	context
	utils
	log
	csv
	archive
)