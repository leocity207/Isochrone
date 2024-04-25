#//////////////////////////////////
# SOURCE FILES
FILE(GLOB NETWORK_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(network STATIC
	${NETWORK_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(network
	coordinate
)

