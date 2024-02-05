#/////////////
# SOURCE FILES
file(GLOB ALGORITHM_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(algorithm STATIC                       
	${ALGORITHM_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(algorithm
	log
	utils
	network
	context
)


