#/////////////
# SOURCE FILES
file(GLOB ALGORITHM_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(reach_algorithm STATIC                       
	${ALGORITHM_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(reach_algorithm
	network
)


