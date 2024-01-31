#//////////////////////////////////
# SOURCE FILES
FILE(GLOB NETWORK_OPTIMIZER_SOURCE "./*.cpp")

#////////
# LIBRARY
add_library(network_optimizer STATIC                      
	${NETWORK_OPTIMIZER_SOURCE}
)

#//////////////
# LIBRARY LINKS
target_link_libraries(network_optimizer
	log
	csv
	json
)

