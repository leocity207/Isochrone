#//////////////////////////////////
# SOURCE FILES
FILE(GLOB MAP_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(map STATIC                      
	${MAP_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(map
	context
	network
)

