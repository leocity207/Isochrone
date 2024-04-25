#//////////////////////////////////
# SOURCE FILES
FILE(GLOB CONTEXT_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(context STATIC                      
	${CONTEXT_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(context
	network
	reach_algorithm
)

